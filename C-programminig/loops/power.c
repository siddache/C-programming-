//! "Two numbers are entered through the keyboard. Write a program to find the value of one number raised to the power of another."

#include <stdio.h>
int main (){
    int a ,b ;

    printf("enter the base : ");
    scanf("%d",&a);
    printf("enter the power : ");
    scanf("%d",&b);

    int power =1 ;
    for(int i =1;i<=b;i++){
        power = power *a ;

    }
    printf("%d raise to power %d is :: %d \n ",a,b,power );


    return 0;
}