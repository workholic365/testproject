#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h> 
#include <pthread.h>
#include <time.h>  


void LogWrite(char *logText,char *string);

long get_file_size(char *path);
int del_one_line(const char * path, int del_line);
void thread_test1(void);
void thread_test2(void);
void get_os_time(void);


volatile bool exit_sig = false;
volatile bool quit_sig = false;


#define MAX_BUFF_SIZE (47.9*1024*1024)
//#define MAX_BUFF_SIZE (10*1024*1024)
#define MAX_BUFF_SIZE_ONE_LINE	(1024)

#define filepath "./log.txt"
pthread_mutex_t mutex_log;

static void sig_handler(int sigio);

static void sig_handler(int sigio) {
    if (sigio == SIGQUIT) {
        quit_sig = true;
    } else if ((sigio == SIGINT) || (sigio == SIGTERM)) {
        exit_sig = true;
    }
    return;
}

void wait_ms(unsigned long a) {
    struct timespec dly;
    struct timespec rem;

    dly.tv_sec = a / 1000;
    dly.tv_nsec = ((long)a % 1000) * 1000000;


    if((dly.tv_sec > 0) || ((dly.tv_sec == 0) && (dly.tv_nsec > 100000))) {
        clock_nanosleep(CLOCK_MONOTONIC, 0, &dly, &rem);
    }
    return;
}


static char * settime(char * time_s){
 time_t timer=time(NULL);
 strftime(time_s, 20, "%Y-%m-%d %H:%M:%S",localtime(&timer));
 return time_s;

}


long get_file_size(char *path)  
{  
    long filesize = -1;      
    struct stat statbuff;  
    if(stat(path, &statbuff) < 0){  
        return filesize;  
    }else{  
        filesize = statbuff.st_size;  
    }  

    return filesize;  
}

static int PrintfLog(char * logText, char * string){

	FILE * fd = NULL;
	char s[1024];
	char tmp[256];
	
	long int file_size ;
	
	fd = fopen(filepath,"a+");
	if(fd == NULL){
		return -1;
	}
	
	get_os_time();
	file_size = get_file_size(filepath);
	//get_os_time();
	printf("file_size is %ld \r\n",file_size);

	get_os_time();
	
	while(file_size >  MAX_BUFF_SIZE)
	{
		del_one_line(filepath,1);

		file_size = get_file_size(filepath);
	}
	
	memset(s, 0, sizeof(s));
	strcpy(s, " [");
	memset(tmp, 0,sizeof(tmp));
	settime(tmp);
	strcat(s, tmp);
	strcat(s, "] ");
	fprintf(fd, "%s", s);
	
	fprintf(fd, "*[%s]:",logText); 
	fprintf(fd, "%s\n",string); 
	fclose(fd);
}


int del_one_line(const char * path, int del_line)
{
    int ret        = -1;
    FILE * fp_r    = NULL;
    FILE * fp_w    = NULL;
    char * buffer  = NULL;
    size_t  sz     = MAX_BUFF_SIZE_ONE_LINE;
    int line_num   = 0;
    int count      = 0;
    int i          = 0;
    const char * tmp_path = "a";
    char read_buff[MAX_BUFF_SIZE_ONE_LINE] = { 0 };
	
	char sys_order[128];
#if 1
    if(path == NULL || del_line < 0)
    {
        fprintf(stderr, "args error");
        return -1;
    }
    
    //1.open file used read only and write only
    fp_r = fopen(path, "r+");
    if(fp_r == NULL)
    {
        fprintf(stderr, "fp_r open error\n");
        return -1;
    }

    fp_w = fopen(tmp_path, "w+");
    if(fp_w == NULL)
    {
         perror("fopen tmp_path");
         return -2;
    }
#endif
    //2.get file line number
    
    buffer = (char *) malloc(sz*sizeof(size_t));

    while((ret = getline(&buffer, &sz, fp_r)) > 0)
    {
		//printf("line_nuim=%d\r\n",line_num);
        line_num++;
    }
    
    printf("line_num=%d\n", line_num);
    
    if(buffer != NULL)
    {
      free(buffer);
      buffer = NULL;
    }

    if(del_line > line_num)
    {
        fprintf(stderr, "args error\n");
        return -1;
    }
    
    rewind(fp_r);
    //3.read line and write line
    memset(read_buff, 0, sizeof(read_buff));
    for(i=1; i<line_num; ++i)
    {
        fgets(read_buff, MAX_BUFF_SIZE_ONE_LINE, fp_r);      
        if(i==del_line)
        {
            fgets(read_buff, MAX_BUFF_SIZE_ONE_LINE, fp_r);      
        }
        fputs(read_buff, fp_w);
//        printf("%s", read_buff);
    }
    
    fclose(fp_r);
    fclose(fp_w);

    //4.delete tmp file,use final filename
    //rename(tmp_path, path);    
	sprintf(sys_order,"mv %s %s",tmp_path,path);
	system(sys_order);
	
    return 0;
}


void LogWrite(char *logText,char *string)
{
  pthread_mutex_lock(&mutex_log); //lock. 
  PrintfLog(logText, string);                
  pthread_mutex_unlock(&mutex_log); //unlock.            
}


int main()
{
	struct sigaction sigact; /* SIGQUIT&SIGINT&SIGTERM signal handling */
	int i;
	
	pthread_t thrid_test1;
	pthread_t thrid_test2;
	
	i = pthread_create( &thrid_test1, NULL, (void * (*)(void *))thread_test1, NULL);
    if (i != 0) {
        printf("ERROR: [main] impossible to create thread_test1 thread\n");
        exit(EXIT_FAILURE);
    }
	
	i = pthread_create( &thrid_test2, NULL, (void * (*)(void *))thread_test2, NULL);
    if (i != 0) {
        printf("ERROR: [main] impossible to create thread_test2 thread\n");
        exit(EXIT_FAILURE);
    }
	
	/* configure signal handling */
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_handler = sig_handler;
    sigaction(SIGQUIT, &sigact, NULL); /* Ctrl-\ */
    sigaction(SIGINT, &sigact, NULL); /* Ctrl-C */
    sigaction(SIGTERM, &sigact, NULL); /* default "kill" command */
	
	 while (!exit_sig && !quit_sig) {

		//sleep(100);
		wait_ms(100);
    }

	pthread_join(thrid_test1, NULL);
	pthread_join(thrid_test2, NULL);
			
	return 0;
}

void thread_test1(void) {
	
	char teststr[] = "thread_test_1";
	
	while (!exit_sig && !quit_sig) {
		LogWrite(teststr,"Debug");
		sleep(1);
	}
	
	
}

void thread_test2(void) {
	
	char teststr[] = "thread_test2";
	
	while (!exit_sig && !quit_sig) {
		LogWrite(teststr,"Test");
		sleep(1);
	}
}

void get_os_time(void)
{
    struct timespec fetch_time;
    struct tm * x;
    char time_str[100];
    long int time_val;

    clock_gettime(CLOCK_REALTIME, &fetch_time);
    x = gmtime(&(fetch_time.tv_sec)); /* split the UNIX timestamp to its calendar components */

    printf("%04i-%02i-%02iT%02i:%02i:%02i.%06liZ \r\n", (x->tm_year)+1900, (x->tm_mon)+1, x->tm_mday, x->tm_hour, x->tm_min, x->tm_sec, (fetch_time.tv_nsec)/1000); /* ISO 8601 format */

    sprintf(time_str,"%02i%02i",  x->tm_hour + 8, x->tm_min);

}

