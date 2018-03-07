#include "order_controller.h"
#include "../driver/elev.h"
#include "../model.h"

void update_order_list() {
    // Delete fulfilled orders
    if(get_current_floor() != -1) {
        delete_inside_order(get_current_floor());
        delete_outside_order(get_current_floor(), current_direction);
    }

    if(emergency) delete_all_orders();

    // Listen for button presses and add corresponding orders
    for(int floor = 0; floor <= top_floor - 1; floor++){
        if(elev_get_button_signal(BUTTON_CALL_UP, floor)){
            add_outside_order(floor, UP);
            emergency = 0;
        }
    }

    for(int floor = 1; floor <= top_floor; floor++){
        if(elev_get_button_signal(BUTTON_CALL_DOWN, floor)){
            add_outside_order(floor, DOWN);
            emergency = 0;
        }
    }

    for(int floor = 0; floor <= top_floor; floor++){
        if(elev_get_button_signal(BUTTON_COMMAND, floor)){
            add_inside_order(floor);
            emergency = 0;
        }
    }
}
