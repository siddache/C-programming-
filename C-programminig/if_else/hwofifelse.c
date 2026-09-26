/*The Core Concept
The fundamental mathematical tool you need to use here is the modulo operator (usually represented by % in most programming languages). The modulo operator calculates the remainder of a division operation.

If a number is perfectly divisible by 4, dividing it by 4 leaves a remainder of 0.

If a number is not perfectly divisible by 4, it will leave a remainder of 1, 2, or 3.
*/


#include <stdio.h>
 
int main (){
    
    printf("ENTER THE YEAR : ");
    int n;
    scanf("%d",&n);
    if((n%4==0 && n%400==100)||n%100==0)
    {
        printf("%d IS A LEAP YEAR\n",n);
    }
    else  
    {
        printf("%d IS NOT A LEAP YEAR\n",n);
    }


    return 0;
}
