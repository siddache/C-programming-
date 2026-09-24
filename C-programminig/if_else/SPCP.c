
#include <stdio.h>

int main (){
    int cp;
    printf("enter cost price : ");
    scanf("%d",&cp);

    int sp;
    printf("enter seller price : ");
    scanf("%d",&sp);

    if (sp>cp){
        printf("PROFIT \n");
    }
    if(sp<cp) {
        printf("LOSS\n");
    }
    if (sp==cp){
        printf(" no profit and no loss \n");
    }


    return 0;

}