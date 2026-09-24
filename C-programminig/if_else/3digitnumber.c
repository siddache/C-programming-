// cheakinf weather the number is 3 digit or not 
#include <stdio.h>

int main (){

    int a ;
    printf(" ENTER THE NUMBER : ");
    scanf("%d",&a);

    if (a>99 && a<1000)
    {
        printf("%d is 3 digit number \n");

    }else{
        printf("%d is not three  digit number\n ");
    }

    return 0;
}