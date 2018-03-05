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
#include <signal.h>

// Handle Ctrl-C
void INT_handler(int signal);
int keep_running = 1;

int main(int argc, char* argv[]) {
    signal(SIGINT, INT_handler); // Assign interrupt signal to INT_handler()
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

    /* Start elevator.
     * During the startup phase we cannot determine the elevator position, and must
     * therefore move it upwards until it reaches a floor
     */
    initialize_model(UP);
    do {
        update_floor();

        // Light up all floors during startup (if between floors)
        if(last_floor < TOP_FLOOR) last_floor++;
        else last_floor = 0;

        update_view();
    } while (initializing && keep_running);

    // Mainloop
    while (keep_running) {
        /* The order of the controller functions is very important.
         *
         * During each iteration of the mainloop, every controller function will update the model to reflect the
         * current state of the elevator. Some of the functions read from the same parameters of the model that another writes to,
         * which is why the order is crucial. At the end of the loop, the model will be written to the elevator
         * (which in this case is our "view").
         */
        update_floor();
        update_direction();
        update_door();
        update_movement();
        update_order_list(); // Must come after update_door() and update_movement() as this deletes the orders
        update_emergency_state();

        print_model_parameters(); // Used for debugging only

        update_view();

        //Web stuff (not a part of project)
        if(web_enabled) update_web_view();
    }

    return 0;
}

void INT_handler(int signal) {
    moving = 0; // Stop elevator before we quit
    update_view();
    keep_running = 0;
}
