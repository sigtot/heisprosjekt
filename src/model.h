#ifndef HEISPROSJEKT_MODEL_H
#define HEISPROSJEKT_MODEL_H

#endif //HEISPROSJEKT_MODEL_H

typedef enum {up, down} Direction;

Direction current_direction;

int moving;

int at_floor;

int current_floor; // 1-4, 0 for between floors

int last_floor;

/**
 * Arrays to keep track of outside orders
 * They should be "invisible" to the programmer and only accessed
 * through add_outside_order(), is_outside_ordered() and delete_outside_order()
 *
 * Outside up orders:
 * 0: {1, up}
 * 1: {2, up}
 * 2: {3, up}
 *
 * Outside down orders:
 * 0: {2, down}
 * 1: {3, down}
 * 2: {4, down}
 *
 */
int outside_up_orders[3];
int outside_down_orders[3];

int inside_orders[4]; // 1-4

int door_open;

/**
 * Update the elevator through the driver to
 * reflect the model parameters in the
 *
 * @return 0 for success
 */
int update_view();

/**
 * Add outside order
 *
 * @param floor
 * @param direction
 * @return 0 for success, 1 for invalid order
 */
int add_outside_order(int floor, Direction direction);

/**
 * Check if floor is ordered with specified direction
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