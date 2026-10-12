// HW : Display this AP – 4, 7, 10, 13, 16.. upto 'n' terms.
#include <stdio.h>

int main()
{
    // int n;
    // printf("enter the num : ");
    // scanf("%d", &n);

    // for (int i = 4; i <= 3 * n + 1; i = i + 3)
    // {
    //     printf("%d ", i);
    // }
    // return 0;

    ///                    OR   this is without maths we have done by pattern of 3 

    int n; // itni baar loop chalega
    printf("Enter a number : ");
    scanf("%d", &n);
    // 4 7 10 13 16 19 .... upto n number of terms
    // we are going to use extra variables
    int a = 4;
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a);
        a = a + 3;
    }
    return 0;
}