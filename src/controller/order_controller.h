/**
 * @file order_controller.h
 * @brief Controller for adding and deleting orders
 */

#ifndef HEIS_LIGHT_CONTROLLER_H
#define HEIS_LIGHT_CONTROLLER_H

/**
 * Listen for button presses and add corresponding orders
 */
void add_orders();

/**
 * Delete fulfilled orders when we reach a floor.
 * Delete all orders on emergency
 */
void delete_orders();

#endif  // HEIS_LIGHT_CONTROLLER_H
