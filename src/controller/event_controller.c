#include "event_controller.h"
#include "../model.h"
#include "../driver/elev.h"

void listen_and_update_model() {
    current_floor = elev_get_floor_sensor_signal();

    int at_floor = current_floor != -1;
    if(at_floor) last_floor = current_floor;

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
}
