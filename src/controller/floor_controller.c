#include "floor_controller.h"
#include "../model.h"
#include "../driver/elev.h"

void update_floor() {
    set_current_floor(elev_get_floor_sensor_signal());

    if(get_current_floor() != -1) last_floor = get_current_floor();
}
