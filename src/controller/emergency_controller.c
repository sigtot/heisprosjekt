#include "emergency_controller.h"
#include "../driver/elev.h"
#include "../model.h"

void update_emergency_state(){
    stop_button_pressed = elev_get_stop_signal();

    if(stop_button_pressed) {
        emergency = 1;
    } else if (has_unfulfilled_orders()) {
        emergency = 0;
    }
}
