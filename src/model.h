/**
 * @file model.h
 * @brief Contains the entire elevator model.
 */

#ifndef HEISPROSJEKT_MODEL_H
#define HEISPROSJEKT_MODEL_H

#define DOOR_WAIT_TIME 3000

#endif //HEISPROSJEKT_MODEL_H

typedef enum {UP, DOWN} Direction;

/**
* Arrays to keep track of orders
* They should be "invisible" to the programmer and only accessed through the "interface"
* add_outside_order(), is_outside_ordered(), delete_outside_order(),
* add_inside_order(), is_inside_ordered() and delete_inside_order().
* If the associated element is 1, the floor is ordered. 0 if not.
*/
typedef struct {
    int* inside_orders;          // Floors 0 - top_floor
    int* outside_down_orders;    // Floors 1 - top_floor
    int* outside_up_orders;      // Floors 0 - top_floor-1
} Order_list;

/* Model parameters */
int n_floors;
int top_floor;

Direction current_direction;

Order_list order_list;

int moving;

int current_position; // 0-6 (or 0-(top_floor-1)), even = at floor, odd = between floors

int last_floor;

int door_open;

long long door_opened_timestamp; // Unix timestamp (in ms) when the door last opened

int stop_button_pressed;

int emergency;

int in_startup;
/* --------------- */



/**
 * Add outside order
 *
 * @param floor
 * @param direction
 */
void add_outside_order(int floor, Direction direction);

/**
 * Check if certain floor is outside ordered with specified direction
 *
 * @param floor
 * @param direction
 * @return 1 if it is ordered, 0 if not (that includes if the order is invalid)
 */
int is_outside_ordered(int floor, Direction direction);

/**
 * Delete an outside order
 *
 * @param floor
 * @param direction
 */
void delete_outside_order(int floor, Direction direction);

/**
 * Add inside order
 *
 * @param floor
 */
void add_inside_order(int floor);

/**
 * Check if certain floor is inside ordered
 *
 * @param floor
 * @return 1 if it is ordered, 0 if not (that includes if the floor is invalid)
 */
int is_inside_ordered(int floor);

/**
 * Delete inside order
 *
 * @param floor
 */
void delete_inside_order(int floor);

/**
 * Delete all orders (even unfulfilled)
 */
void delete_all_orders();

/**
 * Check if there are orders left to serve
 *
 * @return 1 if there are unfulfilled orders, 0 if not
 */
int has_unfulfilled_orders();

/**
 * Check if orders above elevator exist
 *
 * When the elevator is at a floor, that floor is skipped in the check.
 * Otherwise, all floors are checked.
 *
 * @return 1 if orders exist, 0 if not
 */
int has_orders_above();

/**
 * Check if orders below elevator exist
 *
 * When the elevator is at a floor, that floor is skipped in the check.
 * Otherwise, all floors are checked.
 *
 * @return 1 if orders exist, 0 if not
 */
int has_orders_below();

/**
 * Gets the current floor
 *
 * @return 0 - top_floor or -1 if between floors
 */
int get_current_floor();

/**
 * Sets current floor
 *
 * @param floor 0 - top_floor or -1 if between floors
 */
void set_current_floor(int floor);
