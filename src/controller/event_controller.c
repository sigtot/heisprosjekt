#include "event_controller.h"
#include "../model.h"
#include "../driver/elev.h"

void listen_and_update_model() {
    current_floor = elev_get_floor_sensor_signal() + 1;

    int at_floor = current_floor != 0;
    if(at_floor) last_floor = current_floor;

    // TODO: Button signals
}
