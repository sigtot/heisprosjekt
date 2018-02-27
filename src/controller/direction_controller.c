#include "direction_controller.h"
#include "../model.h"

void update_direction() {
    if(get_current_floor() == TOP_FLOOR) current_direction = DOWN;
    if(get_current_floor() == 0) current_direction = UP;

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
        if(is_outside_ordered(get_current_floor(), DOWN)) current_direction = DOWN;
        if(is_outside_ordered(get_current_floor(), UP)) current_direction = UP;
    }
}
