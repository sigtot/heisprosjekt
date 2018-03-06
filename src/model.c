#include "model.h"
#include "driver/elev.h"
#include <stdio.h>
#include <assert.h>

/**
 * Arrays to keep track of orders
 * They should be "invisible" to the programmer and only accessed through the "interface"
 * add_outside_order(), is_outside_ordered(), delete_outside_order(),
 * add_inside_order(), is_inside_ordered() and delete_inside_order().
 * If the associated element is 1, the floor is ordered. 0 if not.
 */
int inside_orders[N_FLOORS]; // Floors 0 - TOP_FLOOR
int outside_down_orders[N_FLOORS - 1]; // Floors 1 - TOP_FLOOR
int outside_up_orders[N_FLOORS - 1]; // Floors 0 - TOP_FLOOR-1

void update_view(){
    /* Write movement to elevator */
    if(moving) {
        if(current_direction == UP) elev_set_motor_direction(DIRN_UP);
        else if(current_direction == DOWN) elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }

    /* Show orders on the elevator lamps */
    for(int floor = 0; floor <= TOP_FLOOR - 1; floor++){
        int lamp_value = is_outside_ordered(floor, UP);
        elev_set_button_lamp(BUTTON_CALL_UP, floor, lamp_value);
    }

    for(int floor = 1; floor <= TOP_FLOOR; floor++){
        int lamp_value = is_outside_ordered(floor, DOWN);
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, lamp_value);
    }

    for(int floor = 0; floor <= TOP_FLOOR; floor++){
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

void initialize_model(Direction direction) {
    initializing = 1;
    moving = 1;
    current_direction = direction;
    door_open = 0;
    door_opened_timestamp = 0;
    stop_button_pressed = 0;
    emergency = 0;
}

void add_outside_order(int floor, Direction direction) {
    if(direction == UP){
        assert(floor >= 0 && floor <= TOP_FLOOR - 1); // Invalid order
        outside_up_orders[floor] = 1;
    } else {
        assert(floor >= 1 && floor <= TOP_FLOOR); // Invalid order
        outside_down_orders[floor - 1] = 1;
    }
}

int is_outside_ordered(int floor, Direction direction) {
    if(direction == UP){
        if(floor < 0 || floor > TOP_FLOOR - 1) return 0; // Invalid order
        return outside_up_orders[floor];
    } else {
        if(floor < 1 || floor > TOP_FLOOR) return 0; // Invalid order
        return outside_down_orders[floor - 1];
    }
}

void delete_outside_order(int floor, Direction direction) {
    if(direction == UP){
        assert(floor >= 0 && floor <= TOP_FLOOR - 1); // Invalid order
        outside_up_orders[floor] = 0;
    } else {
        assert(floor >= 1 && floor <= TOP_FLOOR); // Invalid order
        outside_down_orders[floor - 1] = 0;
    }
}

void add_inside_order(int floor){
    assert(floor >= 0 && floor <= TOP_FLOOR); // Invalid floor
    inside_orders[floor] = 1;
}

int is_inside_ordered(int floor){
    if(floor < 0 || floor > TOP_FLOOR) return 0; // Invalid floor
    return inside_orders[floor];
}

void delete_inside_order(int floor){
    assert(floor >= 0 && floor <= TOP_FLOOR); // Invalid floor
    inside_orders[floor] = 0;
}

int has_unfulfilled_orders() {
    for(int floor = 0; floor <= TOP_FLOOR - 1; floor++){
        if(floor == get_current_floor() && current_direction == UP) continue;
        if(is_outside_ordered(floor, UP)) return 1;
    }

    for(int floor = 1; floor <= TOP_FLOOR; floor++){
        if(floor == get_current_floor() && current_direction == DOWN) continue;
        if(is_outside_ordered(floor, DOWN)) return 1;
    }

    for(int floor = 0; floor <= TOP_FLOOR; floor++){
        if(floor == get_current_floor()) continue;
        if(is_inside_ordered(floor)) return 1;
    }
    return 0;
}

int has_orders_above() {
    if(get_current_floor() == TOP_FLOOR) return 0;

    int floor_above = (current_position + 2) / 2;

    for(int floor = floor_above; floor <= TOP_FLOOR - 1; floor++){
        if(is_outside_ordered(floor, UP)) return 1;
    }

    for(int floor = floor_above; floor <= TOP_FLOOR; floor++){
        if(is_outside_ordered(floor, DOWN)) return 1;
    }

    for(int floor = floor_above; floor <= TOP_FLOOR; floor++){
        if(is_inside_ordered(floor)) return 1;
    }
    return 0;
}

int has_orders_below() {
    if(get_current_floor() == 0) return 0;

    int floor_below = (current_position - 1) / 2;

    for(int floor = floor_below; floor >= 0; floor--){
        if(is_outside_ordered(floor, UP)) return 1;
    }

    for(int floor = floor_below; floor >= 1; floor--){
        if(is_outside_ordered(floor, DOWN)) return 1;
    }

    for(int floor = floor_below; floor >= 0; floor--){
        if(is_inside_ordered(floor)) return 1;
    }
    return 0;
}

int get_current_floor() {
    int even = current_position % 2 == 0;
    if (even) {
        return current_position / 2; // At floor
    }
    return -1; // Between floors
}

void set_current_floor(int floor) {
    if(floor < -1 || floor > TOP_FLOOR) return; // Error: Outside range

    if(floor == -1){
        if(current_position % 2 == 0){
            // Leaving floor
            if (current_direction == UP) current_position++;
            if (current_direction == DOWN) current_position--;
        }
    } else {
        current_position = floor * 2;
    }
}
