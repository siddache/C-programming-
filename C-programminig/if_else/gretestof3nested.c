// for the 3 value find out the gretest value
#include <stdio.h>
int main()
{
    int x, y, z;

    printf("enter 1st value : ");
    scanf("%d", &x);

    printf("enter 2nd value : ");
    scanf("%d", &y);

    printf("enter 3rd value : ");
    scanf("%d", &z);

    if (x > y) // mean y is out of race
    {
        if (x > z) 
            printf("x is the gretest number \n", x);
        else // x<z
            printf("z is the greatest number \n", z);
    }
    else{// y > x -> x ab sabse bada to nhi hai 
        if(y>z)
         printf("y is the greatest \n",y);
         else //z>y
         printf("z is the greatest number \n",z);

    } 
        

    return 0;
}