#include <stdio.h>
#include <stdlib.h>

#define N 30

int filter_duplicated_data(int a[],int n)
{
    /*********Begin**********/
	int i=0, sentinel;
    for(sentinel=0; i<n; sentinel++){
        for(i=sentinel+1; i<n; i++){
            if(a[i] > a[sentinel]){
                a[sentinel+1] = a[i];
				
                break;
            }
        }
    }
    return sentinel;

    /**********  End  **********/
}

int main()
{
    int a[N]={2,2,2,3,4,4,5,6,6,6,6,7,7,8,9,9,10,10,10,10},i,n=20;
	int test[N];
    printf("The original data:\n");
    for(i=0;i<n;i++) printf("%3d",a[i]);
    n=filter_duplicated_data(a,n);
    printf("\n\nThe data after deleted:\n");
    for(i=0;i<n;i++) printf("%3d",a[i]);
	for(i=0;i<n;i++)
	{
		test[i]=a[i];
	}
    printf("\n\n");
	for(i=0;i<n;i++) printf("%3d",test[i]);
	printf("\n\n");
    return 0;
}
