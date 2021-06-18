#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct tokenRecord
{
    char content[21];
    char status[8];
} tokenRecord;

void main()
{
    tokenRecord t1, storedTokens[100], tokens_arr2[1];
    FILE *fp5;
    fp5 = fopen("tokens.csv", "r");
    int k = 0;
    while (fread(&t1, sizeof(tokenRecord), 1, fp5))
    {
        storedTokens[k] = t1;
        k++;
    }
    fclose(fp5);
    int i, x, n;
    time_t t;
    char token[21] = "";
    char buffer[1];
    n = 20;

    FILE *fp;
    fp = fopen("tokens.csv", "a");
    tokenRecord arr[1];
    /* Initializes random number generator */
    srand((unsigned)time(&t));
    /* generate tokens */
    for (i = 0; i < 17; i++)
    {
        int r = rand() % 10;
        itoa(r, buffer, 10);
        strcat(token, buffer);
    }
    int p, match;
    for (p = 0; p < k; p++)
    {
        if (!strcmp(token, storedTokens[p].content))
        {
            match = 1;
        }
    }
    if (!match)
    {
        printf("\n\tGenerated token: %s", token);
        strcpy(arr[0].content, token);
        strcpy(arr[0].status, "unused");
        fwrite(arr, sizeof(tokenRecord), 1, fp);
    }
    else
        printf("Failed.Token already in the list.");
    fclose(fp);
}