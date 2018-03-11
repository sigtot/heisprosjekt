/**
 * @file web_updater.h
 * @brief NOT A PART OF PROJECT. Updates the web-view with the current model and
 * polls for web-orders
 */

#ifndef HEIS_WEB_UPDATER_H
#define HEIS_WEB_UPDATER_H

/**
 * Update the web model every 0.025 seconds with curl
 *
 * This functionality is just implemented for fun and is not a
 * required part of the elevator project. It can be safely ignored.
 *
 * It should also be noted that it is a bit buggy, especially on the server
 * side.
 * Run the elevator without the --web flag on evaluation just to be sure nothing
 * goes wrong. :)
 */
void update_web_view();

#endif  // HEIS_WEB_UPDATER_H
