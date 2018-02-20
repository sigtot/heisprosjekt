#include "direction_controller.h"
#include "../model.h"

void update_direction() {
    if(current_floor == 3) current_direction = DOWN;
    if(current_floor == 0) current_direction = UP;
}
