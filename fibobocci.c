
#include <stdio.h>
int main()
{


    int n;
    printf("enter the num : ");
    scanf("%d",&n);

    int a=1;
    int b=2;
    int sum=0;
    for(int i =1;i<=n-2;i++)
    {
        sum=a+b;
        a=b;
        b=sum;
    }
    printf("Fibonic is : %d ",sum);
    
    return 0;
}