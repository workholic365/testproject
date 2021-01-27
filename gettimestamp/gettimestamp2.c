#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    
    struct timeval start,stop;
    gettimeofday(&start, NULL);
	uint32_t sec_diff,ms_diff,us_diff;
    
    printf("start: second: %ld\n", start.tv_sec); // 秒
    printf("start: millisecond: %ld\n", start.tv_sec * 1000 + start.tv_usec / 1000); // 毫秒
    printf("start: microsecond: %ld\n", start.tv_sec * 1000000 + start.tv_usec); // 徽秒
    
    sleep(3); // 让程序休眠3秒
    printf("---------------------sleep 3 second-------------------\n");
    
    gettimeofday(&stop, NULL);
        
    printf("stop: second: %ld\n", stop.tv_sec); // 秒
    printf("stop: millisecond: %ld\n", stop.tv_sec * 1000 + stop.tv_usec / 1000); // 毫秒
    printf("stop: microsecond: %ld\n", stop.tv_sec * 1000000 + stop.tv_usec); // 徽秒
	
	sec_diff = stop.tv_sec - start.tv_sec;
	ms_diff = (stop.tv_sec * 1000 + stop.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) ;
	us_diff= (stop.tv_sec * 1000000 + stop.tv_usec)-(start.tv_sec * 1000000 + start.tv_usec);
	
	printf("sec_diff = %d,ms_diff = %d,us_diff=%d\r\n",sec_diff,ms_diff,us_diff);

    return 0;
}