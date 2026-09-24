#include <stdio.h> 

 int main (){

    /// SIMPLE INTEREST = P* R* T / si{simple interest } P = PRINCIPLE , R= RATE , T = TIME
    printf("ENTER P : ");
    
    float p;
    scanf("%f",&p);

    printf("ENTER r : ");
    float r;
    scanf("%f",&r);

    printf("ENTER T : ");
    float t;
    scanf("%f",&t);

    float si = (p*r*t)/100;
    printf("HERE IS THE SIMPLE INTEREST : %f\n",si);



    


     return 0;
 }