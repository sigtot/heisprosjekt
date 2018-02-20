#include "direction_controller.h"
#include "../model.h"

void update_direction() {
    if(current_floor == TOP_FLOOR) current_direction = DOWN;
    if(current_floor == 0) current_direction = UP;

    if(current_floor != -1) {
        // Only orders above
        if(has_orders_above() && !has_orders_below()){
            current_direction = UP;
        }

        // Only orders below
        if(has_orders_below() && !has_orders_above()){
            current_direction = DOWN;
        }

        // If there are only orders on the current floor,
        // set the direction according to those ordered directions
        if(!has_orders_above() && !has_orders_below()){
            if(is_outside_ordered(current_floor, DOWN)) current_direction = DOWN;
            if(is_outside_ordered(current_floor, UP)) current_direction = UP;
        }
    }
}
