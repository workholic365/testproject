/* 利用mmap()来读取/etc/passwd 文件内容*/ 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 
#include <stdio.h>
#include <stdlib.h>


int main()
{
	int fd; 
	void *start; 
	struct stat sb; 
	fd=open("/etc/passwd",O_RDONLY); /*打开/etc/passwd*/ 
	
	fstat(fd,&sb); /*取得文件大小*/ 
	
	start = mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0); 
	
	if(start == MAP_FAILED) /*判断是否映射成功*/ 
		return -1; 
	
	printf("%s",(char *)start); 


	/*
		munmap()用来取消参数start所指的映射内存起始地址，参数length则是欲取消的内存大小。 当进程结束或利用exec相关函数来执行其他程序时，映射内存会自动解除，但关闭对应的文 件描述词时不会解除映射。 
		返回值 如果解除映射成功则返回0，否则返回－1，错误原因存于errno中错误代码EINVAL
	*/
	munmap(start,sb.st_size); /*解除映射*/ 
	close(fd); 
	
	return 0;
}
