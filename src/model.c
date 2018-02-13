#include "model.h"
#include "driver/elev.h"

void update_model(){
    if(moving) {
        if(current_direction == up) elev_set_motor_direction(DIRN_UP);
        else if(current_direction == down) elev_set_motor_direction(DIRN_DOWN);
    } else {
        elev_set_motor_direction(DIRN_STOP);
    }
}
