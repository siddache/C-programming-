// Display the Geometric Progression (GP): 100, 50, 25, ... up to n terms.
#include <stdio.h>
int mian()
{
    int n;
    printf("enter the number : ");
    scanf("%f",&n);

    float a=100.0;
    for(int i=1;i<=n;i++)
    {
        printf("%f",a);
        a=a/2;
    }
    return 0;
}