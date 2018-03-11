#define _BSD_SOURCE
#include "web_updater.h"
#include "model.h"
#include <sys/timeb.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void update_web_view() {
    int update_interval = 25;
    struct timeb timer_msec;
    ftime(&timer_msec);
    int milliseconds = timer_msec.millitm;
    if (milliseconds % update_interval != 0)
        return;

    char data_string[100];
    char command_string[200];
    int direction_up = current_direction ? UP : DOWN;
    sprintf(
        data_string,
        "direction=%d&moving=%d&current_floor=%d&last_floor=%d&door_open=%d",
        direction_up, moving, get_current_floor(), last_floor, door_open);
    sprintf(command_string,
            "/usr/bin/curl -s -d \"%s\" 159.65.58.116/heis-web/CEndpoint.php",
            data_string);

    /* Using libcurl turned out to be too much of a headache,
     * so I'm just running the command directly instead.
     * This is bad i know. */
    FILE* fp;
    char path[1035];

    /* Open the command for reading */
    fp = popen(command_string, "r");
    if (fp == NULL) {
        printf("Failed to curl\n");
    }

    /* Read the command output */
    if (fgets(path, sizeof(path) - 1, fp) != NULL && strlen(path) == 4) {
        for (int i = 0; i < 4; i++) {
            if (path[i] == '1') {
                add_inside_order(i);
            }
        }
    }

    /* Close */
    pclose(fp);
}
