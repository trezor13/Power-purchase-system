#include "customerstruct.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void viewCustomers()
{
    int i = 0, n;
    customer customersArr[1000], c1;
    FILE *fp1;
    fp1 = fopen("customer_info_binary.csv", "r");
    i = 0;
    while (fread(&c1, sizeof(customer), 1, fp1))
    {
        customersArr[i] = c1;
        i++;
    }
    n = i;
    fclose(fp1);
    printf("\n\t%d Total customers found.\n\t=================================", i);
    for (i = 0; i < n; i++)
        printf("\n\t%d) %-20s\t%-20s\t%-20s\t%-20s\t%.2f", i + 1, customersArr[i].customerNames, customersArr[i].category, customersArr[i].cashpowernumber, customersArr[i].lastPurchaseMonth, customersArr[i].monthPurchasedUnits);
}

void addCustomers()
{
    //Insert some data into the file
    int i, n;
    printf("\n\tHow many customers do you want to add? ");
    scanf("%d", &n);
    FILE *fp2;
    customer *c2;
    c2 = (customer *)calloc(3, sizeof(customer));
    fp2 = fopen("customer_info_binary.csv", "a");
    for (i = 0; i < n; i++)
    {
        fgets(c2[i].customerNames, 100, stdin);
        printf("\n\tCustomer %d names: ", i + 1);
        scanf("%[^\n]%*c", c2[i].customerNames);
        printf("\tCategory: ");
        scanf("%s", c2[i].category);
        printf("\tCashpower number: ");
        scanf("%s", c2[i].cashpowernumber);
        printf("\tLast purchase month: ");
        scanf("%s", c2[i].lastPurchaseMonth);
        printf("\tMonth purchase count: ");
        scanf("%f", &c2[i].monthPurchasedUnits);
        fwrite(&c2[i], sizeof(customer), 1, fp2);
    }
    fclose(fp2);
    printf("\n\t=================================\n\t%d Customers registered successfully", n);
}

void main()
{
    int option;
    printf("\n\t=================================\n\t|| Electricity purchase system ||");
    printf("\n\t=================================");
    printf("\n\n\t|| Options\n\t=================================\n\t|| 0) Exit");
    printf("\n\t|| 1) View customers\n\t|| 2) Add a new customer");
choice:
    printf("\n\n\tWhat you want to do (1 or 2): ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        viewCustomers();
        break;
    case 2:
        addCustomers();
        break;
    default:
        exit(132);
    }
    if (option == 1 || option == 2)
        goto choice;
}