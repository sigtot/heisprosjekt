#include "movement_controller.h"
#include "../model.h"

void update_movement() {
    if(!door_open && has_unfulfilled_orders()) {
        moving = 1;
    } else {
        moving = 0;
    }
}
