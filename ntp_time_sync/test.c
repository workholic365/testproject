#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#include "aux.h"
#include "trace.h"
#include "ntp_time_sync.h"

//extern void thread_ntp_time(void);

/* signal handling variables */
volatile bool exit_sig = false; /* 1 -> application terminates cleanly (shut down hardware, close open files, etc) */
volatile bool quit_sig = false; /* 1 -> application terminates without shutting down the hardware */

void thread_ntp_time(void);

uint8_t ntp_update = 0;

int main()
{
	printf("test \r\n");

	int i;
	pthread_t thrid_ntp_time;

	i = pthread_create( &thrid_ntp_time, NULL, (void * (*)(void *))thread_ntp_time, NULL);
    if (i != 0) {
        MSG("ERROR: [main] impossible to create ntp time thread\n");
        exit(EXIT_FAILURE);
    }

	 while (!exit_sig && !quit_sig) {
        /* wait for next reporting interval */
        wait_ms(10);

	}
	
	pthread_cancel(thrid_ntp_time);

	return 0;
}

//sync time to ntp (every 1000 * 60 ms)
void thread_ntp_time(void) {
    uint32_t count = 0;
    uint64_t utc_time_ms = 0;
    struct timeval curtime;
    double x1, x2;

    ntp_update = 0;
    while (!exit_sig && !quit_sig) {
        if ((utc_time_ms == 0) || (count >= 60)) {
            utc_time_ms = get_utc_time_from_ntp();
            if (utc_time_ms > 0) {
                x1 = modf((double)utc_time_ms/1E3, &x2);
                curtime.tv_sec = (time_t)x2;
                curtime.tv_usec = (long)(x1 * 1E6);
                settimeofday(&curtime, NULL);
                MSG("INFO: utc_time_ms: %llu\n", (long long unsigned int)utc_time_ms);
                MSG("INFO: curtime.tv_sec: %ld, curtime.tv_usec: %ld\n", curtime.tv_sec, curtime.tv_usec);

                ntp_update = 1;
            }
            count = 0;
        }

        //wait_ms(60000);
		wait_ms(1000);	
        count++;
    }
}
