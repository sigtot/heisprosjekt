#include "direction_controller.h"
#include "../model.h"

void update_direction() {
    if(get_current_floor() == top_floor) current_direction = DOWN;
    if(get_current_floor() == 0) current_direction = UP;

    // Only update the direction when the door closes, as passengers then will
    // have time to order a floor before the elevator serves the next order
    if(door_open) return;

    // Only orders above (or at the current floor in the current direction)
    if(has_orders_above() && !has_orders_below() && !is_outside_ordered(get_current_floor(), current_direction)){
        current_direction = UP;
    }

    // Only orders below (or at the current floor in the current direction)
    if(has_orders_below() && !has_orders_above() && !is_outside_ordered(get_current_floor(), current_direction)){
        current_direction = DOWN;
    }

    // If there are only orders on the current floor,
    // set the direction according to those ordered directions
    if(get_current_floor() != -1 && !has_orders_above() && !has_orders_below()){
        // Don't switch direction if ordered in the current direction
        if(!is_outside_ordered(get_current_floor(), current_direction)) {
            if (is_outside_ordered(get_current_floor(), DOWN)) current_direction = DOWN;
            if (is_outside_ordered(get_current_floor(), UP)) current_direction = UP;
        }
    }
}
