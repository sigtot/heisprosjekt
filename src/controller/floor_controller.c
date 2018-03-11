#include "floor_controller.h"
#include "../driver/elev.h"
#include "../model.h"

void update_floor() {
    set_current_floor(elev_get_floor_sensor_signal());

    int at_floor = get_current_floor() != -1;
    if(at_floor) {
        last_floor = get_current_floor();
        in_startup = 0; // Startup is finished when we reach a floor
    }
}
