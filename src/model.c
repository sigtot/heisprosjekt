#include "model.h"
#include "driver/elev.h"
#include <stdio.h>
#define clear() printf("\033[H\033[J")

int update_view(){
    /* Write movement to elevator */
    if(moving) {
        if(current_direction == UP) elev_set_motor_direction(DIRN_UP);
        else if(current_direction == DOWN) elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }

    /* Show orders on the elevator lamps */
    for(int floor = 0; floor <= 2; floor++){
        int lamp_value = is_outside_ordered(floor, UP);
        elev_set_button_lamp(BUTTON_CALL_UP, floor, lamp_value);
    }

    for(int floor = 1; floor <= 3; floor++){
        int lamp_value = is_outside_ordered(floor, DOWN);
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, lamp_value);
    }

    for(int floor = 0; floor <= 3; floor++){
        int lamp_value = is_inside_ordered(floor);
        elev_set_button_lamp(BUTTON_COMMAND, floor, lamp_value);
    }

    /* Show last floor on the elevator lamps */
    elev_set_floor_indicator(last_floor);

    return 0;
}

void print_model_parameters(){
    clear();
    printf("Direction: %i\n", current_direction);
    printf("Moving: %i\n", moving);
    printf("Current floor: %i\n", current_floor);
    printf("Last floor: %i\n", last_floor);
    printf("Door open: %i\n", door_open);

    for(int floor = 0; floor <= 2; floor++){
        printf("Floor %i UP: %i ", floor, is_outside_ordered(floor, UP));
    }
    printf("\n");
    for(int floor = 1; floor <= 3; floor++){
        printf("Floor %i DOWN: %i ", floor, is_outside_ordered(floor, DOWN));
    }
}

int add_outside_order(int floor, Direction direction) {
    if(direction == UP){
        if(floor < 0 || floor > 2) return 1; // Invalid order
        outside_up_orders[floor] = 1;
    } else {
        if(floor < 1|| floor > 3) return 1; // Invalid order
        outside_down_orders[floor - 1] = 1;
    }
    return 0;
}

int is_outside_ordered(int floor, Direction direction) {
    if(direction == UP){
        if(floor < 0 || floor > 2) return -1; // Invalid order
        return outside_up_orders[floor];
    } else {
        if(floor < 1 || floor > 3) return -1; // Invalid order
        return outside_down_orders[floor - 1];
    }
}

int delete_outside_order(int floor, Direction direction) {
    if(direction == UP){
        if(floor < 0 || floor > 2) return 1; // Invalid order
        outside_up_orders[floor] = 0;
    } else {
        if(floor < 1 || floor > 3) return 1; // Invalid order
        outside_down_orders[floor - 1] = 0;
    }
    return 0;
}

int add_inside_order(int floor){
    if(floor < 0 || floor > 3) return 1; // Invalid order
    inside_orders[floor] = 1;
    return 0;
}

int is_inside_ordered(int floor){
    if(floor < 0 || floor > 3) return -1; // Invalid order
    return inside_orders[floor];
}

int delete_inside_order(int floor){
    if(floor < 0 || floor > 3) return 1; // Invalid order
    inside_orders[floor] = 0;
    return 0;
}