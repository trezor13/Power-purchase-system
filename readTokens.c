#include <stdio.h>

typedef struct tokenRecord
{
    char content[21];
    char status[8];
} tokenRecord;

void main()
{
    tokenRecord t1;
    FILE *fp4;
    fp4 = fopen("tokens.csv", "r");
    int i = 0;
    while (fread(&t1, sizeof(tokenRecord), 1, fp4))
    {
        printf("\n\t%s,%s", t1.content, t1.status);
        i++;
    }
    printf("\n\t%d tokens found.", i);
    fclose(fp4);
}