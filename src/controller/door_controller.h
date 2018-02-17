#ifndef HEIS_DOOR_CONTROLLER_H
#define HEIS_DOOR_CONTROLLER_H

#endif //HEIS_DOOR_CONTROLLER_H

/**
 * Snippet copied from https://programmingtoddler.wordpress.com/2014/11/09/c-how-to-get-system-timestamp-in-second-millisecond-and-microsecond/
 * @return unix time with milliseconds
 */
long long get_timestamp_in_milliseconds();

/**
 * Opens or closes the door
 * Sets the door opened timestamp if the door opens
 */
void update_door();