// Display this AP – 4, 7, 10, 13, 16, 19... up to 'n' terms (without using the mathematical formula).

#include <stdio.h>

int main() {
    int n;
    printf("Enter a number : ");
    scanf("%d", &n);

    int a = 1;
    for (int i = 1; i <= n; i++) {
        printf("%d ", a);
        a = a * 2;
    }

    return 0;
}