#include "model.h"
#include "driver/elev.h"

int update_view(){
    if(moving) {
        if(current_direction == up) elev_set_motor_direction(DIRN_UP);
        else if(current_direction == down) elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }
    return 0;
}

int add_outside_order(int floor, Direction direction) {
    if(direction == up){
        if(floor < 1 && floor > 3) return 1; // Invalid order
        outside_up_orders[floor - 1] = 1;
    } else {
        if(floor < 2 && floor > 4) return 1; // Invalid order
        outside_down_orders[floor - 2] = 1;
    }
    return 0;
}

int is_outside_ordered_(int floor, Direction direction) {
    if(direction == up){
        if(floor < 1 && floor > 3) return -1; // Invalid order
        return outside_up_orders[floor - 1];
    } else {
        if(floor < 2 && floor > 4) return -1; // Invalid order
        return outside_up_orders[floor - 2];
    }
}

int delete_outside_order(int floor, Direction direction) {
    if(direction == up){
        if(floor < 1 && floor > 3) return 1; // Invalid order
        outside_up_orders[floor - 1] = 0;
    } else {
        if(floor < 2 && floor > 4) return 1; // Invalid order
        outside_down_orders[floor - 2] = 0;
    }
    return 0;
}
