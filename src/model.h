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
 * Outside orders:
 * 0: {4, down}
 * 1: {3, down}
 * 2: {2, down}
 * 3: {3, up}
 * 4: {2, up}
 * 5: {1, up}
 *
 * TODO: We need functions
 *  add_order(int floor, Direction direction);
 *  is_ordered(int floor, Direction direction);
 * to set and read from this array. The array itself should not be "seen"
 * in the implementation
 */
int outside_orders[6];

int inside_orders[4]; // 1-4

int door_open;

void update_model();
