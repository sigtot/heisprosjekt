#include "../model.h"
#include "../driver/elev.h"
#include "order_controller.h"

int update_order_list() {
    // Listen for button presses and add corresponding orders
    for(int floor = 0; floor <= 2; floor++){
        if(elev_get_button_signal(BUTTON_CALL_UP, floor)){
            add_outside_order(floor, UP);
        }
    }

    for(int floor = 1; floor <= 3; floor++){
        if(elev_get_button_signal(BUTTON_CALL_DOWN, floor)){
            add_outside_order(floor, DOWN);
        }
    }

    for(int floor = 0; floor <= 3; floor++){
        if(elev_get_button_signal(BUTTON_COMMAND, floor )){
            add_inside_order(floor);
        }
    }

    // Delete fulfilled orders
    if(current_floor != -1) {
        delete_inside_order(current_floor);
        delete_outside_order(current_floor, current_direction);
    }

    return 0;
}
