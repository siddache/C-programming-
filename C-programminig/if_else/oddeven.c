// TAKE POSITIVE INTEGER INPUT AND TELL IF IT IS EVEN OR ODD

#include <stdio.h>
int main (){
    printf("CHECK WHEATHER THE NUMBER IS EVEN OR ODD : ");
    int n ;
    scanf("%d",&n);
    
    if(n%2==0){
        printf("%d is even number \n ");
    
    }
    // if(n%2!=0){
    //     printf("%d is the odd number \n");
    // }
     else {
        printf("%d is odd numbers \n");
     }
    return 0;

}

   