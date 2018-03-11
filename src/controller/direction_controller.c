#include "direction_controller.h"
#include "../model.h"

void update_direction() {
    if (get_current_floor() == top_floor)
        current_direction = DOWN;
    if (get_current_floor() == 0)
        current_direction = UP;

    // Only update the direction when the door closes, as passengers then will
    // have time to order a floor before the elevator serves the next order
    if (door_open)
        return;

    int only_orders_on_current_floor =
        has_unfulfilled_orders() && !has_orders_above() && !has_orders_below();

    if (!is_outside_ordered(get_current_floor(), current_direction)) {
        // Never switch direction if outside ordered on the current floor in the
        // current direction.
        // Such an order would just be about to be fulfilled, and switching
        // direction right before would prevent that from happening
        if (only_orders_on_current_floor) {
            Direction opposite_direction =
                (current_direction == UP) ? DOWN : UP;
            if (is_outside_ordered(get_current_floor(), opposite_direction)) {
                current_direction = opposite_direction;
            }
        } else {
            // If only ordered above or below, go in that direction
            if (!has_orders_below())
                current_direction = UP;
            if (!has_orders_above())
                current_direction = DOWN;
        }
    }
}
