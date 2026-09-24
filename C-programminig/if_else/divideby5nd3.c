// check wheather the number is divide by 5 and 3 
#include <stdio.h>

int main (){
    int n;
    printf("ENTER THE NUMBER : ");
    scanf("%d",&n);

    if(n%5==0 && n%3==0)
    {
        printf("is divisble by 5 and 3\n");
    }
    else
    {
        printf("is not divisible by 5 and 3 \n");
    }
    return 0;
}