// 1.27.2 video if doubt is there then
#include <stdio.h>
int main()
{
    int n;
    printf("ENETR THE NUMBER : ");
    scanf("%d", &n);

    // if (n % 5 == 0 && n % 3 == 0)
    // {
    //     if (n % 15 != 0)
    //     {
    //         printf("%d is divisible by 5 and 3 but not 15 \n");
    //     }
    //     else
    //     {
    //         printf("%d is divisible by  15 \n");
    //     }


    // in if i have given to bracket in the condition bcz that conditon must run 1st then 15!=0 2nd 
    if ((n % 5 == 0 || n % 3 == 0) && n % 15 != 0)
    {
        printf("%d is divisible by 5 and 3 but not 15 \n ",n);
    }

    else
    {
        printf("%d  is not  matching  the  required condition  \n",n);
    }

    return 0;
}