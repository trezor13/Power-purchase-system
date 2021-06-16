#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c, n;
    printf("Token number is:\n");
    
    for (c = 1; c <= 12; c++)
    {    
        n = rand()%100 + 1;
        printf("%d", n);    
    }
    
    return 0;
}
