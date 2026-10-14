//!


#include <stdio.h>

int main()
{
    int n ,sum;
    printf("enter the num : ");
    scanf("%d", &n);

    int r = 0;
    while (n > 0)
    {
        r = r * 10;
        r = r + (n % 10);

        n = n / 10;
        
    }
    sum=n+r;
    printf("the reverse numbers are  :%d ",sum );

    return 0;
}