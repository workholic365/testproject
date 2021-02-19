/* 动态配置10个struct test 空间*/ 
#include <stdlib.h> 
#include <stdio.h>

struct test 
{
	int a[10]; 
	char b[20]; 
};

int main()
{
	struct test *ptr=calloc(sizeof(struct test),10); 
	if(ptr == NULL)
	{
		printf("calloc failed !\r\n");
	}else{
		printf("calloc success !\r\n");
	}
	
	return 0;
}