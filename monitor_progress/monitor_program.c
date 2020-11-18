/************************************************************
* FileName	：Monitor.c
*
* Author	: Tobiu
*
* Description:	守护 lora_pkt_fwd 进程；
*
* Date		 : 20191210
*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <error.h>
 
#define MAXFILE 	3
#define USEPRINTF 	1
 
/************************************************************
* @Function		：	program_Running
* @Description	:	判断程序是否在运行
* @Param	 	：
*		service	：	进程名
* @return 		：	exist : 1，no found value : 0
***********************************************************/
int program_Running(char *service)
{
	FILE *fp;
	char cmd[128], buf[1024];
	char *pLine;
 
	sprintf(cmd, "/bin/ps -ef | /bin/grep  %s | /bin/grep -v grep", service);
	fp = popen(cmd, "r");
	while( fgets(buf, sizeof(buf), fp) != NULL )
	{
		pLine = strtok(buf, "\n");
		while( pLine )
		{
			if( strstr(pLine, service) )
			{
				pclose( fp );
				return 1;
			}
			pLine = strtok(NULL, "\n");
		}
	}
	pclose( fp );
	return 0;
}
 
int main(int argc, char* argv[])
{
 
	while( 1 ) 
	{
		/*监测 pan_pkt_fwd*/
		if(!program_Running("lora_pkt_fwd"))
		{
			/* The program did not run */
			system("/bin/killall  lora_pkt_fwd");		//杀进程
			system("/home/lora_pkt_fwd &");		//restart lora_pkt_fwd ,which located in /home
		}
		else{
			//printf("\r\n");
		}
		sleep(3);
	} 			
	return 0;
}
