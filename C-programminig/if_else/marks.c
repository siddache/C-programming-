// else if concept 
#include <stdio.h>
int main()
{
    int n;
    printf("ENTER THE NUMBER TO CHECK GRADE : ");
    scanf("%d", &n);
    // more than 80---A
    // more than 60----b
    // more than 40---c
    // less than 40--fails

    // if (n > 80)
    // {
    //     printf("A Grade : %d\n",n);
    // }
    // if (n > 60)
    // {
    //     printf("B Grade : %d\n",n);
    // }
    // if (n > 40)
    // {
    //     printf("C Grade : %d\n",n);
    // }
    // if (n <= 40)
    // {
    //     printf("FAiLS Grade : %d\n",n);
    // }

    if (n > 80)
    {
        printf("A Grade : %d\n",n);
    }
    else if (n > 60)
    {
        printf("B Grade : %d\n",n);
    }
    else if (n > 40)
    {
        printf("C Grade : %d\n",n);
    }
    else
    {
        printf("FAiLS  : %d\n",n);
    }

    return 0;
}