#include <stdio.h>
#include <stdlib.h>
#include "sys_stat.h"

#define STATUS_SIZE     200
char status_report[STATUS_SIZE]; /* status report as a JSON object */

int main()
{

	float cpu_ratio = 0.0;
    float mem_ratio = 0.0;

	get_mem_ratio(&mem_ratio);
	get_cpu_ratio(&cpu_ratio);

	snprintf(status_report, STATUS_SIZE, "\"stat\":{\"cpur\":%.1f,\"memr\":%.1f}",100.0 * cpu_ratio, 100.0 * mem_ratio);
     
	printf("status_report is %s \r\n",status_report);	

	return 0;
}
