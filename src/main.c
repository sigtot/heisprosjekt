/**
 * @file main.c
 * @brief Main program file
 */

#include "controller/main_controller.h"
#include <string.h>
#include <signal.h>

#include "web_updater.h"

/**
 * Handle interrupt signal (Ctrl-C)
 * @param signal is a dummy parameter that still needs to be passed
 */
void INT_handler(int signal);

int main(int argc, char* argv[]) {
    signal(SIGINT, INT_handler);  // Assign interrupt signal to INT_handler()
    int web_enabled = 0;  // Web view of the elevator (not a part of project)

    // Loop over command line flags
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--web") == 0 || strcmp(argv[i], "-w") == 0)
            web_enabled = 1;
    }

    initialize();

    // Mainloop
    while (1) {
        update_model();
        update_elevator();

        // Web view of the elevator (not a part of project)
        if (web_enabled)
            update_web_view();
    }

    return 0;
}

void INT_handler(int signal) {
    terminate(0);
}
