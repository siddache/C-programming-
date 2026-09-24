// find out the greatest number between the four numbers
#include <stdio.h>
int main()
{
    int a;
    printf("enter the a number : ");
    scanf("%d", &a);

    int b;
    printf("enter the b number : ");
    scanf("%d", &b);

    int c;
    printf("enter the c number : ");
    scanf("%d", &c);

    int d;
    printf("enter the d number : ");
    scanf("%d", &d);

    if (a > b && a > c && a > d)
    {
        printf("a is greather number \n");
    }
    if (b > a && b > c && b > d)
    {
        printf("b is greather number \n");
    }
    if (c > a && c > b && c > d)
    {
        printf("c is greather number \n");
    }
    if (d > a && d > b && d > c)
    {
        printf("d is greather number \n1");
    }

    return 0;
}