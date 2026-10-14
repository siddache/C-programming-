//! WAP FOR TO COUNT A DIGIT BY N NUMBER OF NUMBERS 
#include <stdio.h>

int main(){
    int n ;
    printf("ENTER THE NUMBERS : ");
    scanf("%d",&n);

    int count = 0;
    while(n!=0){
        n=n/10;
       
        count++;
        
    }
    printf(" HERE ARE THE TOTAL DIGIT : %d",count);

    return 0;
}