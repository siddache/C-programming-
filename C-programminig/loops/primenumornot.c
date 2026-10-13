// Write a program in C to check whether a given positive integer $n$ is a prime number or not.

#include <stdio.h>

int main()
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("Neither prime nor composite\n");
        return 0;
    }

    int a = 0;

    for (int i = 2; i <= n - 1; i++)
    {
        if (n % i == 0)
        {
            a = 1;
            break; // break is used for teminate ( stop )
        }
    }

    if (a == 0)
        printf("The given number is prime\n");
    else
        printf("The given number is composite\n");

    return 0;
}
