#include "movement_controller.h"
#include "../model.h"

void update_movement() {
    if(door_open || emergency || !has_unfulfilled_orders()){
        moving = 0;
    } else {
        moving = 1;
    }
}
