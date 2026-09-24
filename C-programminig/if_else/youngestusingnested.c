// HW : If the ages of Ram, Shyam and Ajay are input through the keyboard, write a program to determine the youngest of the three.
#include <stdio.h>
int main()
{
    int ram, shyam, ajay;

    printf("ENTER RAM AGE : ");
    scanf("%d", &ram);

    printf("ENTER SHYAM AGE : ");
    scanf("%d", &shyam);

    printf("ENTER AJAY AGE : ");
    scanf("%d", &ajay);

    if (ram < shyam)
    { // ram is small
        if (ram < ajay)
        {
            printf("%d ram is youngest kid \n",ram);
        }
        else// ajay < ram
        {
            printf("%d ajay is youngest kid \n",ajay);
        }
    }
    else
    {
        if(shyam<ajay){
            printf("%d shyam is the youngest kid \n",shyam);
        }else{
            printf("%d ajay is youngest kid \n ",ajay);
        }
    }

    return 0;
}