
//! Print the sum of this series: 1 - 2 + 3 - 4 + 5 - 6... upto 'n'.

#include <stdio.h>
int main()
{
    int n;
    printf("enter the the digit : ");
    scanf("%d", &n);

    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        //! this code this for normal sum
        //! ques 1+2+3... n
        //  sum=sum+i;

        //! ques is 1-2+3-4+5...n terms

        if (i % 2 != 0)
            sum = sum + i;
        else
            sum = sum - i;
    }
    printf("sum : %d\n", sum);

    return 0;
}