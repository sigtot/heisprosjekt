#include "driver/elev.h"
#include "model.h"
#include "controller/floor_controller.h"
#include "controller/door_controller.h"
#include "controller/movement_controller.h"
#include "controller/order_controller.h"
#include "controller/direction_controller.h"
#include "web_updater.h"
#include "controller/emergency_controller.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int web_enabled = 0; // Web stuff (not a part of project)

    // Loop over command line flags
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "--web") == 0 || strcmp(argv[i], "-w") == 0) web_enabled = 1;
    }

    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    // Initialize model values
    initialize_model(UP);
    do {
        update_floor();

        // Light up all floors during startup (if between floors)
        if(last_floor < TOP_FLOOR) last_floor++;
        else last_floor = 0;

        update_view();
    } while (initializing);

    // Mainloop
    while (1) {
        // The order of these is very important
        update_floor();
        update_direction();
        update_door();
        update_movement();
        update_order_list(); // Must come after update_door() and update_movement() as this deletes the orders
        update_emergency_state();

        print_model_parameters();
        update_view();

        //Web stuff (not a part of project)
        if(web_enabled) update_web_view();
    }

    return 0;
}
