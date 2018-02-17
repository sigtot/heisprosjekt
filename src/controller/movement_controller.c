#include "movement_controller.h"
#include "../model.h"

void update_movement() {
    if(!door_open && has_orders_not_on_current_floor()) {
        moving = 1;
    } else {
        moving = 0;
    }
}
