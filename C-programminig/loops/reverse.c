//! WAP to print the reverse of a given number & store it. (Example: n = 12345, r = 54321)

#include <stdio.h>

int main()
{
    int n;
    printf("enter the num : ");
    scanf("%d", &n);

    int r = 0;
    while (n > 0)
    {
        r = r * 10;
        r = r + (n % 10);

        n = n / 10;
    }
    printf("the reverse numbers are  :%d ", r);

    return 0;
}