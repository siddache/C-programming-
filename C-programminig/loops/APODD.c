// HW: Print the table of 'n'. Here 'n' is an integer which user will input.

#include <stdio.h>

int main()
{
    int n;
    printf("enter the number : ");
    scanf("%d",&n);

    for(int i=1;i<=2*n-1;i=i+2)
    {
        printf("%d ",i);
    }

    return 0;
}