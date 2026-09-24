
#include <stdio.h>
 int main (){

    int n;
    printf("ENTER NUMBER : ");
    scanf("%d",&n);
    if(n<0){ // if n is negative
        n=n*(-1);

    }
    printf("THE ABSOLUTE VALUE IS : %d\n",n);
    


    return 0;
 }