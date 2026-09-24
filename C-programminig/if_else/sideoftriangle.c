// find out the greatest number between the four numbers
#include <stdio.h>
int main()
{
    int a;
    printf("enter the side of a  : ");
    scanf("%d", &a);

    int b;
    printf("enter the side of b : ");
    scanf("%d", &b);

    int c;
    printf("enter the side of c : ");
    scanf("%d", &c);

    

    if ((a + b) > c && (a + c) > b && (b + c) > a)
    {
        printf("vaild triangle \n");
    }

    else
    {
        printf("invaild triangle \n");
    }

    return 0;
}