//!

#include <stdio.h>

int main()
{
    int n, sum,lastDigit;
    printf("enter the num : ");
    scanf("%d", &n);

    int r = 0;
    while (n > 0)
    {
        r = r * 10;
        r = r + (n % 10);
        sum = sum + lastDigit; 

        n = n / 10;
    }
    sum = n + r;
    printf("the reverse numbers are  :%d ", sum);

    return 0;
}