#include "driver/elev.h"
#include "model.h"
#include "controller/floor_controller.h"
#include "controller/order_controller.h"
#include <stdio.h>

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    moving = 1;
    update_view();

    while (1) {
        // UP-DOWN state machine
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            current_direction = DOWN;
            update_view();
        } else if (elev_get_floor_sensor_signal() == 0) {
            current_direction = UP;
            update_view();
        }

        update_floor();
        update_order_list();

        print_model_parameters();
        update_view();


        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            moving = 0;
            update_view();
            break;
        }
    }

    return 0;
}
