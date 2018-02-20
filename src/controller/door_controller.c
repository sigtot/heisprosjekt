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
    int door_wait_time_over = door_opened_timestamp < get_timestamp_in_milliseconds() - DOOR_WAIT_TIME;

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

    /* Logic to open the door when the elevator is ordered from the current floor */

    // Elevator is waiting to go up and someone wants to get on and go up
    int a = (is_outside_ordered(current_floor, UP) && current_direction == UP && has_orders_above());

    // Elevator is waiting to go down and someone wants to get on and go down
    int b = (is_outside_ordered(current_floor, DOWN) && current_direction == DOWN && has_orders_below());

    // Elevator has fulfilled all orders and someone wants to get on
    int c = !has_orders_not_on_current_floor() && (is_outside_ordered(current_floor, UP) || is_outside_ordered(current_floor, DOWN));

    if(!moving && (a || b || c)){
        door_open = 1;
        door_opened_timestamp = get_timestamp_in_milliseconds();
    }

    /* --------- */
}