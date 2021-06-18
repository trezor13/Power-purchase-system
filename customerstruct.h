#include <stdio.h>

typedef struct customer
{
    char customerNames[100];
    char category[100];
    char cashpowernumber[12];
    char lastPurchaseMonth[12];
    float monthPurchasedUnits;
} customer;