#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>


#define RESULT_ERR  -1
#define RESULT_OK   0

#define GATEWAY_PROGRAMME_NAME  "pppd"  //you can define any proc name here

static int GetPidByName(pid_t *pid, const char* pName);

int main()
{
    pid_t pidV = 0;

    if(GetPidByName(&pidV, GATEWAY_PROGRAMME_NAME) != RESULT_OK)
    {
        printf("GetPidByName Error!\n");
    }
    else{
        printf("GetPidByName OK!\n");
        printf("pidV is %d \n",pidV);
    }

    return 0;
}


static int GetPidByName(pid_t *pid, const char* pName)
{
    DIR *dir;
    struct dirent *ptr;
    FILE *fp;
    char filepath[50] = { 0 };
    char cur_task_name[50] = { 0 };
    char buf[1024] = { 0 };

    if((NULL == pid) || (NULL == pName))
    {
        return RESULT_ERR;
    }

    dir = opendir("/proc"); 
    if (NULL != dir)
    {
        while ((ptr = readdir(dir)) != NULL) //循环读取/proc下的每一个文件/文件夹
        {
            //如果读取到的是"."或者".."则跳过，读取到的不是文件夹名字也跳过
            if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
                continue;
            if (DT_DIR != ptr->d_type)
                continue;

            sprintf(filepath, "/proc/%s/status", ptr->d_name);//生成要读取的文件的路径
            fp = fopen(filepath, "r");
            if (NULL != fp)
            {
                if( fgets(buf, 1023, fp)== NULL ){
                    fclose(fp);
                    continue;
                }
                sscanf(buf, "%*s %s", cur_task_name);
        
                //如果文件内容满足要求则打印路径的名字（即进程的PID）
                if (!strcmp(pName, cur_task_name)){
                    sscanf(ptr->d_name, "%d", pid);
                    fclose(fp);
                    closedir(dir);
                    
                    return RESULT_OK;
                }
                fclose(fp);
            }
        }
        closedir(dir);
    }

    return RESULT_ERR;
}

