#include "floor_controller.h"
#include "../model.h"
#include "../driver/elev.h"

void update_floor() {
    current_floor = elev_get_floor_sensor_signal();

    int at_floor = current_floor != -1;
    if(at_floor) last_floor = current_floor;
}
