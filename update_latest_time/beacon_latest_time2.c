#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "sqlite3.h"
#include <string.h>



char db_file[] = "/www/cgi-bin/conf.db";
char beacon_table1[] = "Beacon_Config";



char * get_os_time(void)
{
    struct timespec fetch_time;
    struct tm * x;
    char time_str[100];
    long int time_val;

    clock_gettime(CLOCK_REALTIME, &fetch_time);
    x = gmtime(&(fetch_time.tv_sec)); /* split the UNIX timestamp to its calendar components */
    //snprintf(fetch_timestamp, sizeof fetch_timestamp, "%04i-%02i-%02iT%02i:%02i:%02i.%06liZ", (x->tm_year)+1900, (x->tm_mon)+1, x->tm_mday, x->tm_hour, x->tm_min, x->tm_sec, (fetch_time.tv_nsec)/1000); /* ISO 8601 format */

    printf("%04i-%02i-%02i-%02i:%02i:%02i.%06liZ", (x->tm_year)+1900, (x->tm_mon)+1, x->tm_mday, x->tm_hour+8, x->tm_min, x->tm_sec, (fetch_time.tv_nsec)/1000); /* ISO 8601 format */
    sprintf(time_str,"%04i-%02i-%02i-%02i:%02i:%02i", (x->tm_year)+1900, (x->tm_mon)+1, x->tm_mday, x->tm_hour+8, x->tm_min, x->tm_sec);

    return time_str;
}

void update_devEui_Update_flag(char *dbfile,char *dbtable,char * beac_time)
{
    int row,col;
    char **result;
    sqlite3 *db=NULL;
    int i,j;
    int ret = 0;
	char update_buff[1024];

    if(sqlite3_open(dbfile, &db)!=0)
    {
        printf("cann't open %s\r\n",dbfile);
    }

    //get value from db_table1
    memset(update_buff,0,100);
	
	//sprintf(sql, "update  Beacon_Config  set  beacon_period='%lu'",beac_perid_tmp);
    sprintf(update_buff,"update  Beacon_Config  set  beacon_latest_time='%s'",beac_time);

    ret = sqlite3_exec(db, update_buff, NULL, NULL, NULL);

    sqlite3_close(db);
}
 


int main()
{
	char current_os_time[100];
	
	while(1)
	{
		
		
		update_devEui_Update_flag(db_file,beacon_table1,get_os_time());
		
		sleep(10);
	}
	
	return 0;
}
