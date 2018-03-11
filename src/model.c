#include "model.h"
#include <assert.h>

void add_outside_order(int floor, Direction direction) {
    if (direction == UP) {
        assert(floor >= 0 && floor <= top_floor - 1);  // Invalid order
        order_list.outside_up_orders[floor] = 1;
    } else {
        assert(floor >= 1 && floor <= top_floor);  // Invalid order
        order_list.outside_down_orders[floor - 1] = 1;
    }
}

int is_outside_ordered(int floor, Direction direction) {
    if (direction == UP) {
        if (floor < 0 || floor > top_floor - 1)
            return 0;  // Invalid order
        return order_list.outside_up_orders[floor];
    } else {
        if (floor < 1 || floor > top_floor)
            return 0;  // Invalid order
        return order_list.outside_down_orders[floor - 1];
    }
}

void delete_outside_order(int floor, Direction direction) {
    if (direction == UP) {
        assert(floor >= 0 && floor <= top_floor - 1);  // Invalid order
        order_list.outside_up_orders[floor] = 0;
    } else {
        assert(floor >= 1 && floor <= top_floor);  // Invalid order
        order_list.outside_down_orders[floor - 1] = 0;
    }
}

void add_inside_order(int floor) {
    assert(floor >= 0 && floor <= top_floor);  // Invalid floor
    order_list.inside_orders[floor] = 1;
}

int is_inside_ordered(int floor) {
    if (floor < 0 || floor > top_floor)
        return 0;  // Invalid floor
    return order_list.inside_orders[floor];
}

void delete_inside_order(int floor) {
    assert(floor >= 0 && floor <= top_floor);  // Invalid floor
    order_list.inside_orders[floor] = 0;
}

void delete_all_orders() {
    for (int floor = 0; floor <= top_floor - 1; floor++) {
        delete_outside_order(floor, UP);
    }

    for (int floor = 1; floor <= top_floor; floor++) {
        delete_outside_order(floor, DOWN);
    }

    for (int floor = 0; floor <= top_floor; floor++) {
        delete_inside_order(floor);
    }
}

int has_unfulfilled_orders() {
    for (int floor = 0; floor <= top_floor - 1; floor++) {
        if (floor == get_current_floor() && current_direction == UP)
            continue;
        if (is_outside_ordered(floor, UP))
            return 1;
    }

    for (int floor = 1; floor <= top_floor; floor++) {
        if (floor == get_current_floor() && current_direction == DOWN)
            continue;
        if (is_outside_ordered(floor, DOWN))
            return 1;
    }

    for (int floor = 0; floor <= top_floor; floor++) {
        if (floor == get_current_floor())
            continue;
        if (is_inside_ordered(floor))
            return 1;
    }
    return 0;
}

int has_orders_above() {
    if (get_current_floor() == top_floor)
        return 0;

    int floor_above = (current_position + 2) / 2;

    for (int floor = floor_above; floor <= top_floor - 1; floor++) {
        if (is_outside_ordered(floor, UP))
            return 1;
    }

    for (int floor = floor_above; floor <= top_floor; floor++) {
        if (is_outside_ordered(floor, DOWN))
            return 1;
    }

    for (int floor = floor_above; floor <= top_floor; floor++) {
        if (is_inside_ordered(floor))
            return 1;
    }
    return 0;
}

int has_orders_below() {
    if (get_current_floor() == 0)
        return 0;

    int floor_below = (current_position - 1) / 2;

    for (int floor = floor_below; floor >= 0; floor--) {
        if (is_outside_ordered(floor, UP))
            return 1;
    }

    for (int floor = floor_below; floor >= 1; floor--) {
        if (is_outside_ordered(floor, DOWN))
            return 1;
    }

    for (int floor = floor_below; floor >= 0; floor--) {
        if (is_inside_ordered(floor))
            return 1;
    }
    return 0;
}

int get_current_floor() {
    int even = current_position % 2 == 0;
    if (even) {
        return current_position / 2;  // At floor
    }
    return -1;  // Between floors
}

void set_current_floor(int floor) {
    if (floor < -1 || floor > top_floor)
        return;  // Error: Outside range

    if (floor == -1) {
        if (current_position % 2 == 0) {
            // Leaving floor
            if (current_direction == UP)
                current_position++;
            if (current_direction == DOWN)
                current_position--;
        }
    } else {
        current_position = floor * 2;
    }
}
