// diffrence between n=2 and n==2 in this example in this
#include <stdio.h>

int main()
{
    int n = 2;
    if (n == 2)
        printf("good morninig\n ");
    // printf("hello world ");  this will show error in the code
    else
    {
        printf("good evening \n");
    }

    return 0;
}