#include "main_controller.h"
#include <stdlib.h>
#include <stdio.h>

// The controller should access both the elevator and the model
#include "../driver/elev.h"
#include "../model.h"

// This main controller should run all the other controller actions
#include "floor_controller.h"
#include "direction_controller.h"
#include "door_controller.h"
#include "movement_controller.h"
#include "order_controller.h"
#include "emergency_controller.h"

void update_elevator() {
    /* Write movement to elevator */
    if (moving) {
        if (current_direction == UP)
            elev_set_motor_direction(DIRN_UP);
        else if (current_direction == DOWN)
            elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }

    /* Show orders on the elevator lamps */
    for (int floor = 0; floor <= top_floor - 1; floor++) {
        int lamp_value = is_outside_ordered(floor, UP);
        elev_set_button_lamp(BUTTON_CALL_UP, floor, lamp_value);
    }

    for (int floor = 1; floor <= top_floor; floor++) {
        int lamp_value = is_outside_ordered(floor, DOWN);
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, lamp_value);
    }

    for (int floor = 0; floor <= top_floor; floor++) {
        int lamp_value = is_inside_ordered(floor);
        elev_set_button_lamp(BUTTON_COMMAND, floor, lamp_value);
    }

    /* Show last floor on the elevator lamps */
    elev_set_floor_indicator(last_floor);

    /* Indicate open door with open door lamp */
    elev_set_door_open_lamp(door_open);

    /* Indicate stop button being pressed */
    elev_set_stop_lamp(stop_button_pressed);
}

/*
 * The order of the controller functions is very important.
 * During each iteration of the mainloop, every controller function will update
 * the model to reflect the current state of the elevator. Some of the functions
 * read from the same parameters of the model that another writes to, which is
 * why the order is crucial. At the end of the loop, the model will be written
 * to the elevator.
 *
 * Note that update_direction() is ran both before and after update_door() and
 * update_movement(). It needs to be ran before, since the direction should
 * change immediately when we reach the top or bottom. It also needs to be ran
 * after, since, in certain cases, the direction should change immediately after
 * closing the door. If it doesn't, the door will wait for 3 more seconds before
 * closing.
 *
 */
void update_model() {
    update_floor();
    add_orders();
    update_emergency_state();

    update_direction();
    update_door();
    update_movement();
    update_direction();

    delete_orders();
}

void initialize() {
    // Set initial model parameters
    init_model(N_FLOORS);

    // Initialize elevator
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        terminate(1);
    }

    // Move elevator into defined state
    while (in_startup) {
        update_floor();

        // Light up all floors during startup (if between floors)
        if (last_floor < top_floor)
            last_floor++;
        else
            last_floor = 0;

        update_elevator();
    }
}

void terminate(int exit_code) {
    moving = 0;
    update_elevator();

    destroy_model();

    exit(exit_code);
}
