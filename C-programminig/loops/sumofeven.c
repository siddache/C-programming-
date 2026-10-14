//! wap tp print sum of all the even digits of a given  number

#include <stdio.h>

int main()
{

    int n;
    printf("enter the the digit : ");
    scanf("%d", &n);

    int sum = 0;
    while (n != 0)
    {
        int lastDigit = n % 10; // Extract the last digit
        sum = sum + lastDigit;  // Add it to the sum
        n = n / 10;             // Remove the last digit
    }
    printf("here is sum of the digits : %d", sum);

    return 0;
}

