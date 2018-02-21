#include "web_updater.h"
#include "model.h"
#include <sys/timeb.h>
#include <curl/curl.h>
#include <stdio.h>

void update_web_view() {
    int update_interval = 100;
    struct timeb timer_msec;
    ftime(&timer_msec);
    int milliseconds = timer_msec.millitm;
    if(milliseconds % update_interval != 0) return;

    CURL *curl;

    /* Get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        char data_string [100];
        int direction_up = current_direction ? UP : DOWN;
        sprintf(data_string, "direction=%d&moving=%d&current_floor=%d&last_floor=%d&door_open=%d",
                direction_up, moving, current_floor, last_floor, door_open);

        /* Set url and data */
        curl_easy_setopt(curl, CURLOPT_URL, "159.65.58.116/heis-web/");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        /* Perform the request*/
        curl_easy_perform(curl);

        /* Cleanup */
        curl_easy_cleanup(curl);
    }
}
