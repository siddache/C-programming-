// CHECKKKING WHEATHER THE NO. IS DIVISIBLE BY 5 OR NOT 

#include <stdio.h>
int main (){
    printf("DOES NO. IS DIVISIBLE BY 5 OR NOT :  ");
    int n ;
    scanf("%d",&n);
    
    if(n%5==0){
        printf("%d DIVISIBLE BY 5 \n ");
    
    }
    
     else {
        printf("%d NOT DIVISIBLE BY 5\n");
     }
    return 0;

}