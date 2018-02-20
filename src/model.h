#include "driver/elev.h"

#ifndef HEISPROSJEKT_MODEL_H
#define HEISPROSJEKT_MODEL_H

#define TOP_FLOOR N_FLOORS - 1
#define DOOR_WAIT_TIME 3000

#endif //HEISPROSJEKT_MODEL_H

typedef enum {UP, DOWN} Direction;

Direction current_direction;

int moving;

int current_floor; // 0-3, -1 for between floors

int last_floor;

int door_open;

long long door_opened_timestamp; // The time when the door last opened

/**
 * If the associated element is 1, the floor is ordered. 0 if not.
 */
int inside_orders[4]; // Floors 0-3

/**
 * Arrays to keep track of outside orders
 * They should be "invisible" to the programmer and only accessed
 * through add_outside_order(), is_outside_ordered() and delete_outside_order()
 * If the associated element is 1, the floor is ordered. 0 if not.
 *
 * Outside up orders:
 * 0: {0, up}
 * 1: {1, up}
 * 2: {2, up}
 *
 * Outside down orders:
 * 0: {1, down}
 * 1: {2, down}
 * 2: {3, down}
 *
 */
int outside_up_orders[3];
int outside_down_orders[3];

/**
 * Update elevator to match model
 *
 * @return 0 for success
 */
int update_view();

void print_model_parameters();

/**
 * Add outside order
 *
 * @param floor
 * @param direction
 * @return 0 for success, 1 for invalid order
 */
int add_outside_order(int floor, Direction direction);

/**
 * Check if floor is outside ordered with specified direction
 *
 * @param floor
 * @param direction
 * @return 1 if it is ordered, 0 if not, -1 if invalid order
 */
int is_outside_ordered(int floor, Direction direction);

/**
 * Delete an order
 *
 * @param floor
 * @param direction
 * @return 0 for success, 1 for invalid order
 */
int delete_outside_order(int floor, Direction direction);

/**
 * Add inside order
 *
 * @param floor
 * @return 0 for success, 1 for invalid order
 */
int add_inside_order(int floor);

/**
 * Check if certain floor is inside ordered
 *
 * @param floor
 * @return 1 if it is ordered, 0 if not, -1 if invalid order
 */
int is_inside_ordered(int floor);

/**
 * Delete inside order
 *
 * @param floor
 * @return 0 for success, 1 for invalid order
 */
int delete_inside_order(int floor);

/**
 * Check if any floor is ordered
 *
 * @return 1 if orders exist, 0 if not
 */
int has_orders_not_on_current_floor();

/**
 * Check if there are orders left to serve
 *
 * @return 1 if there are unfulfilled orders, 0 if not
 */
int has_unfulfilled_orders();

/**
 * WARNING: Does not work between floors
 * @return 1 if orders exist, 0 if not
 */
int has_orders_above();

/**
 * WARNING: Does not work between floors
 * @return 1 if orders exist, 0 if not
 */
int has_orders_below();