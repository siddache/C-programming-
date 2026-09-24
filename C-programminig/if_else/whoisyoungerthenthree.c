// 
#include <stdio.h>

int main (){
    int a;
    printf("age of the 1st person : ");
    scanf("%d",&a);
    int b;
    printf("age of the 2nd person : ");
    scanf("%d",&b);
    int c;
    printf("age of the 3rd person : ");
    scanf("%d",&c);

    if(a<b && a<c){
        printf("%d is younger person \n",a);
    }
    if(b<a && b<c){
        printf("%d is younger person \n",b);
    }
    if(c<b && c<a){
        printf("%d is younger person \n",c);
    }
    

    return 0;
}