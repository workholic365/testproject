/*
返回一分页的大小，单位为字节（byte）。此为系统的分页大小，不一定会和硬件分页大小相同。
返回值:内存分页大小。附加说明在Intel x86 上其返回值应为4096bytes。
*/

#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("page size = %d\n",getpagesize( ) );	
}
