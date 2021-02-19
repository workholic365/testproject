/*
	memchr 在某一内存范围中查找一特定字符 
	相关函数 index，rindex，strchr，strpbrk，strrchr，strsep，strspn，strstr 
	表头文件 #include<string.h> 
	定义函数 void *memchr(const void *s, int c, size_t n); 
	函数说明 memchr()从头开始搜寻s所指的内存内容前n个字节，直到发现第一个值为c的字节，则返回指 向该字节的指针。 
	返回值 如果找到指定的字节则返回该字节的指针，否则返回0。 范例
*/

#include <string.h>
#include <stdio.h>

#define TEST1 1
#define TEST2 0

int main()
{
#if TEST1
	char *s = "0123456789012345678901234567890";

	char *p; 
	p = memchr(s,'5',10); 
	printf("%s\n",p); 
#endif

#if TEST2
	char *s = "012345678012345678901234567890";
	char *p;
	p = memchr(s,'9',10);
	printf("%s\n",p);
#endif
	return 0;
}
