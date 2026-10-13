// Write a program in C to print all odd numbers from $1$ to $100$ using the continue statement.

#include <stdio.h>

int main()
{
    // for (int i=1 ; i<=100 ; i++){
    //     if(i%2==0){
    //         continue;
    //         printf("%d",i);
    //     }
    //     printf("%d ",i);
    // }


    /// for even num HW 

    for (int i=1 ; i<=100 ; i++){
        if(i%2!=0){
            continue;
            printf("%d",i);
        }
        printf("%d ",i);
    }
    return 0;
}