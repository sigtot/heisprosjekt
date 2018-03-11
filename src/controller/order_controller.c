#include "order_controller.h"
#include "../driver/elev.h"
#include "../model.h"

void add_orders() {
    // Listen for button presses and add corresponding orders
    for(int floor = 0; floor <= top_floor - 1; floor++){
        if(elev_get_button_signal(BUTTON_CALL_UP, floor)){
            add_outside_order(floor, UP);
        }
    }

    for(int floor = 1; floor <= top_floor; floor++){
        if(elev_get_button_signal(BUTTON_CALL_DOWN, floor)){
            add_outside_order(floor, DOWN);
        }
    }

    for(int floor = 0; floor <= top_floor; floor++){
        if(elev_get_button_signal(BUTTON_COMMAND, floor)){
            add_inside_order(floor);
        }
    }
}

void delete_orders() {
    if(emergency){
        delete_all_orders();
        return;
    }

    // Delete fulfilled orders
    int at_floor = get_current_floor() != -1;
    if(at_floor) {
        delete_inside_order(get_current_floor());
        if(!((get_current_floor() == 0 && current_direction == DOWN) ||
                (get_current_floor() == top_floor && current_direction == UP))) {
            delete_outside_order(get_current_floor(), current_direction);
        }
    }
}
