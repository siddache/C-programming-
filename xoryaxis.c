// 
#include <stdio.h>
int main (){
    int x,y;
    printf("enter the value of x  : ");
    scanf("%d",&x);

    printf("enter the value of y  : ");
    scanf("%d",&y);

      if(y==0 && x==0){
        printf(" lies on origin  ");
      }
      else if (y==0){
        printf("lies on x axis  ");
      }
      else if (x==0)
        {
            printf("lies on y axis ");
        }
        else{
            printf("neither on the axes nor at the origin");
        }
    return 0;
}
 