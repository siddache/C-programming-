
#include <stdio.h>

int main()
{
    int n;
    printf("enetr the num : ");
    scanf("%d", &n);

    int i = 1;
    while (i <= n)
    {
        i = n % 10;
    }
    i++;
    printf("%d", i);

    return 0;
}
