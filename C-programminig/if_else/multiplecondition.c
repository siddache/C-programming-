// find out the greatest number between the three number
#include <stdio.h>
int main()
{
    int a;
    printf("enter the number a : ");
    scanf("%d", &a);

    int b;
    printf("enter the number b : ");
    scanf("%d", &b);

    int c;
    printf("enter the number c : ");
    scanf("%d", &c);

    if (a > b && a > c)
    {
        printf("a is the greather number \n");
    }
    if (b > a && b > c)
    {
        printf(" b is the greather number \n");
    }

    if (a > b && a > c)
    {
        printf("%d is the greather number \n");
    }

    if (c > a && c > b)
    {
        printf("c is the greather number \n");
    }

    return 0;
}