// Ques : Given three points (x1, y1), (x2, y2) and (x3, y3), write a program to check if all the three points fall on one straight line.
#include <stdio.h>
int main()
{
    double x1, x2, x3, y1, y2, y3;

    printf("enter x1 :");
    scanf("%lf", &x1);

    printf("enter x2 :");
    scanf("%lf", &x2);

    printf("enter x3 :");
    scanf("%lf", &x3);

    printf("enter y1 :");
    scanf("%lf", &y1);

    printf("enter y2 :");
    scanf("%lf", &y2);

    printf("enter y3 :");
    scanf("%lf", &y3);

    double M1 = (y2 - y1) * (x3 - x2);
    double M2 = (y3 - y2) * (x2 - x1);

    if (M1 ==M2)
    {
        printf("ALL THE THREE POINTS FALL ON ONE STRAIGHT LINE\n");
    }
    else 
    {
        printf("ALL THE THREE POINTS not FALL ON ONE STRAIGHT LINE\n");
    }

    return 0;
}