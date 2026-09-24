//  check weather the number is divisible by 5 or 3 
#include <stdio.h>
int main(){

    int n;
    printf(" ENTER THE NUMBER : ");
    scanf("%d",&n);

    if(n%5==0 || n%3==0 ){
        printf("THIS NUMBER IS DIVISIBLE BY 5 OR 3 \n");

    }
    else{
        printf("THIS NUMBER IS  not DIVISIBLE BY 5 OR 3 \n");


    }
    return 0;
}