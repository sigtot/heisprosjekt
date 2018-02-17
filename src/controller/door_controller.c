#include "door_controller.h"
#include "../model.h"
#include <stdio.h>

#include <sys/timeb.h>

long long get_timestamp_in_milliseconds() {
    struct timeb timer_msec;
    long long int timestamp_msec;
    if (!ftime(&timer_msec)) {
        timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                         (long long int) timer_msec.millitm;
    }
    else {
        timestamp_msec = -1;
    }
    return timestamp_msec;
}

void update_door() {
    if(current_floor == -1){
        return;
    }

    int has_been_ordered_here = is_inside_ordered(current_floor) || is_outside_ordered(current_floor, current_direction);
    int door_wait_time_over = door_opened_timestamp < get_timestamp_in_milliseconds() - 3000;

    if(has_been_ordered_here) {
        door_open = 1; // Open the door
        door_opened_timestamp = get_timestamp_in_milliseconds();
        return;
    }

    if(!moving && !door_wait_time_over) {
        door_open = 1; // Keep the door open
    } else {
        door_open = 0; // Close it
    }
}
