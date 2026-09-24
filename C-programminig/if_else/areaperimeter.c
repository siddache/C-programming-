#include <stdio.h>

int main (){
    int l;
    printf("enter length : ");
    scanf("%d",&l);

    int b;
    printf("enter the breath : ");
    scanf("%d",&b);
    int A=l*b;
    int P=2*(l+b); 

    if(A>P){

        A=l*b;
        printf("area is greather than perimeter  \n");

    }
   
    if 
    (P>A){
        
      
        printf("area is not greater than perimeter \n");
    }
    
    


    return 0;
}