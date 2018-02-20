#include "driver/elev.h"
#include "model.h"
#include "controller/floor_controller.h"
#include "controller/door_controller.h"
#include "controller/movement_controller.h"
#include "controller/order_controller.h"
#include "controller/direction_controller.h"
#include <stdio.h>
#include <time.h>

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    moving = 1;
    door_open = 0;
    door_opened_timestamp = 0;
    update_view();

    // Mainloop
    while (1) {
        // The order of these is very important
        update_floor();
        update_direction();
        update_door();
        update_movement();
        update_order_list(); // Must come after update_door() and update_movement() as this deletes the orders

        print_model_parameters();
        update_view();

        // Emergency stop pressed
        if (elev_get_stop_signal()) emergency = 1;
    }

    return 0;
}
