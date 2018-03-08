#include "door_controller.h"
#include "../model.h"

#include <sys/timeb.h>

/**
 * Snippet copied from https://programmingtoddler.wordpress.com/2014/11/09/c-how-to-get-system-timestamp-in-second-millisecond-and-microsecond/
 * @return unix time with milliseconds
 */
long long get_timestamp_in_milliseconds();

void update_door() {
    if(get_current_floor() == -1){
        return;
    }

    int has_been_ordered_here = is_inside_ordered(get_current_floor()) || is_outside_ordered(get_current_floor(), current_direction);

    if(has_been_ordered_here || stop_button_pressed) {
        door_open = 1; // Open the door
        door_opened_timestamp = get_timestamp_in_milliseconds();
    }

    int door_wait_time_over = door_opened_timestamp < get_timestamp_in_milliseconds() - DOOR_WAIT_TIME;

    if(door_wait_time_over){
        door_open = 0;
    }
}

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
