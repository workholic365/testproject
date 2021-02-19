#include <stdio.h>
#include <stdlib.h> 
int main() 
{
	char *a="-100.23"; 
	char *b="200e-2"; 
	float c; 
	c = atof(a) + atof(b); 
	printf("c=%.2f\n",c); 
}