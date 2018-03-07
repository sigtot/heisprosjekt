#include "main_controller.h"
#include <malloc.h>
#include <stdlib.h>

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

void update_elevator(){
    /* Write movement to elevator */
    if(moving) {
        if(current_direction == UP) elev_set_motor_direction(DIRN_UP);
        else if(current_direction == DOWN) elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }

    /* Show orders on the elevator lamps */
    for(int floor = 0; floor <= top_floor - 1; floor++){
        int lamp_value = is_outside_ordered(floor, UP);
        elev_set_button_lamp(BUTTON_CALL_UP, floor, lamp_value);
    }

    for(int floor = 1; floor <= top_floor; floor++){
        int lamp_value = is_outside_ordered(floor, DOWN);
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, lamp_value);
    }

    for(int floor = 0; floor <= top_floor; floor++){
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
 * During each iteration of the mainloop, every controller function will update the model to reflect the
 * current state of the elevator. Some of the functions read from the same parameters of the model that another writes to,
 * which is why the order is crucial. At the end of the loop, the model will be written to the elevator.
 */
void update_model(){
    update_floor();
    update_direction();
    update_door();
    update_movement();
    update_order_list();
    update_emergency_state();
}

void initialize() {
    // Set initial model parameters
    in_startup = 1;
    moving = 1;
    current_direction = UP;
    door_open = 0;
    door_opened_timestamp = 0;
    stop_button_pressed = 0;
    emergency = 0;
    n_floors = N_FLOORS;
    top_floor = n_floors - 1;
    order_list = (Order_list) { .inside_orders=malloc(n_floors*sizeof(int)),
                                .outside_down_orders=malloc((n_floors - 1)*sizeof(int)),
                                .outside_up_orders=malloc((n_floors - 1)*sizeof(int))};

    // Initialize elevator
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        terminate();
    }

    // Move elevator into defined state
    do {
        update_floor();

        // Light up all floors during startup (if between floors)
        if(last_floor < top_floor) last_floor++;
        else last_floor = 0;

        update_elevator();
    } while (in_startup);
}

void terminate() {
    moving = 0;
    update_elevator();

    free(order_list.inside_orders);
    free(order_list.outside_down_orders);
    free(order_list.outside_up_orders);

    exit(1);
}
