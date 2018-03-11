/**
 * @file main_controller.h
 * @brief The middleman between the elevator and the model. Also initializes and terminates the elevator.
 */

#ifndef HEIS_MAIN_CONTROLLER_H
#define HEIS_MAIN_CONTROLLER_H

#endif //HEIS_MAIN_CONTROLLER_H

/**
 * Update the physical elevator to match model
 */
void update_elevator();

/**
 * Update model to reflect changes in the elevator and in the model itself.
 *
 * A wrapper function for all the controller functions
 */
void update_model();

/**
 * Initialize entire system (both hardware and model) and set initial model parameters.
 *
 * At the beginning of the program, the elevator is in an undefined state where its position is unknown.
 * This function moves the elevator up until it reaches a floor, thereby bringing it out of the undefined state.
 */
void initialize();

/**
 *  Stop elevator, free up memory used in order arrays and exit the program
 */
void terminate(int exit_code);
