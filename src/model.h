#include "driver/elev.h"

#ifndef HEISPROSJEKT_MODEL_H
#define HEISPROSJEKT_MODEL_H

#define TOP_FLOOR N_FLOORS - 1
#define DOOR_WAIT_TIME 3000

#endif //HEISPROSJEKT_MODEL_H

typedef enum {UP, DOWN} Direction;


/** Model parameters **/
Direction current_direction;

int moving;

int current_position; // 0-6 (or 0-(TOP_FLOOR-1)), even = at floor, odd = between floors

int last_floor;

int door_open;

long long door_opened_timestamp; // Unix timestamp (in ms) when the door last opened

int stop_button_pressed;
int emergency;

int initializing;
/** --------------- **/


/**
 * Update elevator to match model
 */
void update_view();

/**
 * Set all the initial model values
 *
 * @param direction UP or DOWN to configure startup-direction
 */
void initialize_model(Direction direction);

/**
 * Add outside order
 *
 * @param floor
 * @param direction
 */
void add_outside_order(int floor, Direction direction);

/**
 * Check if floor is outside ordered with specified direction
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
 * @return 0 - TOP_FLOOR or -1 if between floors
 */
int get_current_floor();

/**
 * Sets current floor
 * @param floor 0 - TOP_FLOOR or -1 if between floors
 */
void set_current_floor(int floor);
