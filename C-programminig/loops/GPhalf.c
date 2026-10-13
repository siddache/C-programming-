// Display the Geometric Progression (GP): 100, 50, 25, ... up to n terms.
#include <stdio.h>
int main()
{
    int n;
    printf("enter the number : ");
    scanf("%d", &n);

    float a = 100.0;
    for (int i = 1; i <= n; i++)
    {
        printf("%.2f ", a);
        a = a / 2.0;
    }

    // int n;
    // printf("Enter number of terms: ");
    // scanf("%d", &n);

    // float a = 100.0;
    // for (int i = 1; i <= n; i++) {
    //     printf("%.2f ", a); // %.2f prints up to 2 decimal places
    //     a = a / 2.0;
    // }

    // return 0;
}
