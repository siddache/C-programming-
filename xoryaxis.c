// 
#include <stdio.h>
int main (){
    int x,y;
    printf("enter the value of x and y : ");
      scanf("%d %d ",&x , &y);

      if(y==0 && x==0){
        printf(" lies on origin  ");
      }
      else if (x==0){
        printf("lies on y axis  ");
      }
      else if (y==0)
        {
            printf("lies on x axis ");
        }
        else{
            printf("neither on the axes nor at the origin");
        }

    






    return 0;
}
 