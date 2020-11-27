/* -------------------------------------------------------------------------- */
/* --- DEPENDANCIES --------------------------------------------------------- */

/* fix an issue between POSIX and C99 */
#if __STDC_VERSION__ >= 199901L
    #define _XOPEN_SOURCE 600
#else
    #define _XOPEN_SOURCE 500
#endif

#include <stdio.h>  /* printf fprintf */
#include <time.h>   /* clock_nanosleep */
#include <stdint.h>
#include <sys/time.h>
#include "aux.h"

/* -------------------------------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */

#if DEBUG_AUX == 1
    #define DEBUG_MSG(str)                fprintf(stderr, str)
    #define DEBUG_PRINTF(fmt, args...)    fprintf(stderr,"%s:%d: "fmt, __FUNCTION__, __LINE__, args)
#else
    #define DEBUG_MSG(str)
    #define DEBUG_PRINTF(fmt, args...)
#endif

/* -------------------------------------------------------------------------- */
/* --- PUBLIC FUNCTIONS DEFINITION ------------------------------------------ */

/* This implementation is POSIX-pecific and require a fix to be compatible with C99 */
void wait_ms(unsigned long a) {
    struct timespec dly;
    struct timespec rem;

    dly.tv_sec = a / 1000;
    dly.tv_nsec = ((long)a % 1000) * 1000000;

    DEBUG_PRINTF("NOTE dly: %ld sec %ld ns\n", dly.tv_sec, dly.tv_nsec);

    if((dly.tv_sec > 0) || ((dly.tv_sec == 0) && (dly.tv_nsec > 100000))) {
        clock_nanosleep(CLOCK_MONOTONIC, 0, &dly, &rem);
        DEBUG_PRINTF("NOTE remain: %ld sec %ld ns\n", rem.tv_sec, rem.tv_nsec);
    }
}

void wait_us(unsigned long a) {
    struct timespec dly;
    struct timespec rem;

    dly.tv_sec = a / 1000000;
    dly.tv_nsec = ((long)a % 1000000) * 1000;

    //MSG("NOTE dly: %ld sec %ld ns\n", dly.tv_sec, dly.tv_nsec);

    if((dly.tv_sec > 0) || ((dly.tv_sec == 0) && (dly.tv_nsec > 100000))) {
        clock_nanosleep(CLOCK_MONOTONIC, 0, &dly, &rem);
    }
}

/**
 * @brief get current time (unit:s)
 * @param[in] <none>
 * @return time_val:consist of tm_hour & tm_min
 */
long  int get_current_time_s(void)
{
    struct timeval tv;
	long  int time_s;

    gettimeofday(&tv, NULL);

    time_s = tv.tv_sec;
	//printf("time_s = %ld\n",time_s);

    return time_s;
    
}

/**
 * @brief get current time (unit:us)
 * @param[in] <none>
 * @return time_val:consist of tm_hour & tm_min
 */
long long int get_current_time_us(void)
{
    struct timeval tv;
	long long int  time_us;

    gettimeofday(&tv, NULL);

    time_us = (long long )tv.tv_sec * 1000000 + tv.tv_usec ;
	
    return time_us;
    
}

/**
 * @brief get current time (unit:ms)
 * @param[in] <none>
 * @return time_val:consist of tm_hour & tm_min
 */
long long int get_current_time_ms(void)
{
    struct timeval tv;
    long long int time_ms;

    gettimeofday(&tv, NULL);

    time_ms = (long long )tv.tv_sec * 1000 + tv.tv_usec/1000 ;
	//printf("time_ms = %ld\n",time_ms);
    return time_ms;
}


/**
 * @brief get current time of OS
 * @param[in] <none>
 * @return time_val:consist of tm_hour & tm_min
 */
void get_current_os_time(void)
{
    struct timespec fetch_time;
    struct tm * x;

    clock_gettime(CLOCK_REALTIME, &fetch_time);
    x = gmtime(&(fetch_time.tv_sec)); /* split the UNIX timestamp to its calendar components */

    printf("%04i-%02i-%02iT%02i:%02i:%02i.%06liZ \r\n", (x->tm_year)+1900, (x->tm_mon)+1, x->tm_mday, x->tm_hour, x->tm_min, x->tm_sec, (fetch_time.tv_nsec)/1000); /* ISO 8601 format */
}


/* --- EOF ------------------------------------------------------------------ */

