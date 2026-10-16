        // Online C compiler (editor)
// Write and run C online using this editor.

#include <stdio.h>

int main() {
    int n ;
    
    scanf("%d",&n);
    
    int r=1;
    int i=1;
    while(i<=n){
        r=n%10;
    }
    i++;
    printf("%d",r);
    
	return 0;

}


