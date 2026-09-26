#include <stdio.h> 
 int main () 
 {
    int n ;
    printf("ENTER THE NUMBER : ");
    scanf("%d",&n);
    

    // if (n%2==0){
    //     printf("%d is even number \n");
        

    // }else {
    //     printf("%d is odd number \n");
    // }

    n%2==0 ? printf("even num : ") : printf("odd num : ") ;

     return 0;
 }