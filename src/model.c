#include "model.h"
#include "driver/elev.h"
#include <stdio.h>
#define clear() printf("\033[H\033[J")

int update_view(){
    /* Write to elevator */
    if(moving) {
        if(current_direction == up) elev_set_motor_direction(DIRN_UP);
        else if(current_direction == down) elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }

    return 0;
}

void print_model_parameters(){
    clear();
    printf("Direction: %i\n", current_direction);
    printf("Moving: %i\n", moving);
    printf("Current floor: %i\n", current_floor);
    printf("Last floor: %i\n", last_floor);
    printf("Door open: %i\n", door_open);

    for(int floor = 1; floor <= 3; floor++){
        printf("Floor %i up: %i ", floor, is_outside_ordered(floor, up));
    }
    printf("\n");
    for(int floor = 2; floor <= 4; floor++){
        printf("Floor %i up: %i ", floor, is_outside_ordered(floor, down));
    }
}

int add_outside_order(int floor, Direction direction) {
    if(direction == up){
        if(floor < 1 || floor > 3) return 1; // Invalid order
        outside_up_orders[floor - 1] = 1;
    } else {
        if(floor < 2 || floor > 4) return 1; // Invalid order
        outside_down_orders[floor - 2] = 1;
    }
    return 0;
}

int is_outside_ordered(int floor, Direction direction) {
    if(direction == up){
        if(floor < 1 || floor > 3) return -1; // Invalid order
        return outside_up_orders[floor - 1];
    } else {
        if(floor < 2 || floor > 4) return -1; // Invalid order
        return outside_up_orders[floor - 2];
    }
}

int delete_outside_order(int floor, Direction direction) {
    if(direction == up){
        if(floor < 1 || floor > 3) return 1; // Invalid order
        outside_up_orders[floor - 1] = 0;
    } else {
        if(floor < 2 || floor > 4) return 1; // Invalid order
        outside_down_orders[floor - 2] = 0;
    }
    return 0;
}

int add_inside_order(int floor){
    if(floor < 1 || floor > 4) return 1; // Invalid order
    inside_orders[floor - 1] = 1;
    return 0;
}

int is_inside_ordered(int floor){
    if(floor < 1 || floor > 4) return -1; // Invalid order
    return inside_orders[floor - 1];
}

int delete_inside_order(int floor){
    if(floor < 1 || floor > 4) return 1; // Invalid order
    inside_orders[floor -1] = 0;
    return 0;
}