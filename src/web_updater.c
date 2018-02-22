#include "web_updater.h"
#include "model.h"
#include <sys/timeb.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_string);

        /* Perform the request*/
        curl_easy_perform(curl);

        /* Cleanup */
        curl_easy_cleanup(curl);
    }
}

void get_orders_from_web() {
    /* Putting the curled data into a string turned out to be
     * too much of a headache, so I'm just running curl
     * directly :) This is bad, i know */
    FILE *fp;
    char path[1035];

    /* Open the command for reading */
    fp = popen("/usr/bin/curl -s 159.65.58.116/heis-web/orders.php", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output */
    if (fgets(path, sizeof(path)-1, fp) != NULL && strlen(path) == 4) {
        for(int i = 0; i < 4; i++) {
            if(path[i] == '1') {
                add_inside_order(i);
            }
        }
    }

    /* close */
    pclose(fp);
}
