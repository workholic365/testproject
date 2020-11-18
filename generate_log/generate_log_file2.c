#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_BUFF_SIZE (50)

char test_file[] = "./log_file.txt";

long get_file_size(char *path);

int print_debug_mes_to_file(char *msg, char *save_file);

int del_one_line(const char * path, int del_line);

int main()
{
	FILE *fp;
	int file_size;

	char teststr[] = "test1 test1";
	char teststr2[] = "test2 test2";
	char teststr3[] = "test3 test3";

	print_debug_mes_to_file(teststr,test_file);
			
	return 0;
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

int print_debug_mes_to_file(char *msg, char *save_file)
{
	int file_size ;
	char str_tmp[1024] = "test for log file exceed";

	FILE *fd = fopen(save_file, "a+");
    if (fd == NULL)
    {
        printf("fd is NULL and it will create a new log file named  %s  \n",test_file);
    }

	file_size = get_file_size(save_file);


	while(file_size >  MAX_BUFF_SIZE)
	{
		del_one_line(save_file,1);

		file_size = get_file_size(save_file);
	}

	printf("current file size is %d ,it will continue writing msg into %s \r\n",file_size,save_file);

	if (msg && msg[0] != 0)
    {
        fwrite(msg, strlen(msg), 1, fd);
        char *next = "\n";
        fwrite(next, strlen(next), 1, fd);
    }

    fclose(fd);

}


int del_one_line(const char * path, int del_line)
{
    int ret        = -1;
    FILE * fp_r    = NULL;
    FILE * fp_w    = NULL;
    char * buffer  = NULL;
    size_t  sz     = MAX_BUFF_SIZE;
    int line_num   = 0;
    int count      = 0;
    int i          = 0;
    const char * tmp_path = "a";
    char read_buff[MAX_BUFF_SIZE] = { 0 };
	
	char sys_order[128];
    
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

    //2.get file line number
    
    buffer = (char *) malloc(sz*sizeof(size_t));
    while((ret = getline(&buffer, &sz, fp_r)) > 0)
    {
        line_num++;
    }
    
//    printf("line_num=%d\n", line_num);
    
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
        fgets(read_buff, MAX_BUFF_SIZE, fp_r);      
        if(i==del_line)
        {
            fgets(read_buff, MAX_BUFF_SIZE, fp_r);      
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


