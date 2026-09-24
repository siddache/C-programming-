// Ques : Take input percentage of a student and print the Grade according to marks:
//  90-100 Excellent
//  80-90 Very Good   70-80 Good   60-70 Can do better   50-60 Average   40-50 Below Average   <40 Fail

#include <stdio.h>
int main()
{

    int n;
    printf("ENTER THE PERCENTAGE : ");
    scanf("%d", &n);

    if (n > 90 && n <= 100)
    {
        printf("Excellent\n");
    }
    else if(n > 80 && n<=90)
    {
        printf("very good \n");
    }
    else if(n > 70 && n<=80)
    {
        printf(" good\n ");
    }
    else if(n > 60 && n<=70)
    {
        printf("Can do bette\n");

    }
    else if(n > 50 && n<=60)
    {
        printf("Average\n");

    }
    else if(n > 40 && n<=50)
    {
        printf("Below Average\n");

    }
    else if(n>0 && n<=40){
        printf("you failed bcz of adi and pmax playing poker with them\n");
    }
    else{
        printf("U ARE GYATT\n");
    }
    


    return 0;
}
