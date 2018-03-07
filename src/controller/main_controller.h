#ifndef HEIS_MAIN_CONTROLLER_H
#define HEIS_MAIN_CONTROLLER_H

#endif //HEIS_MAIN_CONTROLLER_H

/**
 * Update elevator to match model
 */
void update_elevator();

/**
 * Update model to reflect changes in the elevator and in the model itself
 */
void update_model();

/**
 * Initialize entire system, both hardware and model and set the initial model parameters
 */
void initialize();

/**
 *  Stop elevator and free up memory used in order arrays
 */
void terminate();