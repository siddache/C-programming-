#include <stdio.h>

int main()
{

    int n,LastDigit;
    printf("enter the the digit : ");
    scanf("%d", &n);

int sum = 0;
while (n != 0)
{

    int lastDigit = n % 10; // Extract the last digit
    if(lastDigit%2==0){
    sum = sum + lastDigit;
    }
      // Add it to the sum
    n = n / 10;  
                     // Remove the last digit
}
printf("here is sum of the digits : %d", sum);

return 0;
}
