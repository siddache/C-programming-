#include <stdio.h>

int main(){
    
    int a,b;
    printf("enter the first number : ");
    scanf("%d",&a);
    printf("enter the second number : ");
    scanf("%d",&b);

    if (a>b)
    {
        printf("%d is greater than %d \n",a,b);
    }else{
        printf("%d is greater than %d \n",b,a);
    }
    printf("thank you for using this program \n");
    return 0;
}