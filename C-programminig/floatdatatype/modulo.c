#include <stdio.h>

int main (){

    printf("a : ");
    int a ;
    scanf("%d",&a);

    printf("b : ");
    int b;
    scanf("%d",&b);

    int z = a%b;
    printf("module : %d\n",z);


    return 0;
}