//! The goal is to take a number (e.g., 1234), find its reverse (4321), and add them together (1234 + 4321 = 5555).

#include <stdio.h>

int main()
{
    int n, sum,lastDigit;
    printf("enter the num : ");
    scanf("%d", &n);

    int originalNum = n;
    int r = 0;
    while (n > 0)
    {
        r = r * 10;
        r = r + (n % 10);
        

        n = n / 10;
        
    }
     sum = originalNum+r;
    
    printf("The sum of the number and its reverse is: %d\n", sum);

    return 0;
}

