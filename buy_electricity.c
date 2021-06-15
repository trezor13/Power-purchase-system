#include "customerstruct.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main()
{
	char cashpower_input[21], names[100], category[100], lastPurchaseMonth[12];
	char *months[12];
	months[0] = "January";
	months[1] = "February";
	months[2] = "March";
	months[3] = "April";
	months[4] = "May";
	months[5] = "June";
	months[6] = "July";
	months[7] = "August";
	months[8] = "September";
	months[9] = "October";
	months[10] = "November";
	months[11] = "December";
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char *currentMon = months[tm.tm_mon];
	int monthPurchasedUnits, customer_index;
	int input_amount, i = 0, j = 0, cashpower_valid = 0, final_units, n;
	customer customersArr[1000];
	printf("\n\t=================================\n\t|| Electricity purchase system ||\n\t=================================");
inputcashpower:
	printf("\n\tEnter your cashpower number: ");
	scanf("%s", cashpower_input);
	// Get the list of customers from the csv file
	customer c1;
	FILE *fp1;
	fp1 = fopen("customer_info_binary.csv", "r");
	i = 0;
	while (fread(&c1, sizeof(customer), 1, fp1))
	{
		customersArr[i] = c1;
		i++;
	}
	n = i;
	i = 0;
	for (j = 0; j < n; j++)
	{
		if (!strcmp(customersArr[j].cashpowernumber, cashpower_input))
		{
			customer rightOne = customersArr[j];
			cashpower_valid = 1;
			customer_index = j;
			strcpy(names, rightOne.customerNames);
			strcpy(category, rightOne.category);
			strcpy(lastPurchaseMonth, rightOne.lastPurchaseMonth);
			monthPurchasedUnits = rightOne.monthPurchasedUnits;
		}
	}
	j = 0;
	if (!cashpower_valid)
	{
		printf("\n\tInvalid cashpower number! Please try again.");
		goto inputcashpower;
	}
	else
	{
		if (!strcmp(lastPurchaseMonth, currentMon))
		{
			FILE *fp3;
			fp3 = fopen("customer_info_binary.csv", "w");
			strcpy(customersArr[customer_index].lastPurchaseMonth, currentMon);
			customersArr[customer_index].monthPurchasedUnits = 0;

			for (i = 0; i < n; i++)
				fwrite(&customersArr[i], sizeof(customer), 1, fp3);
		}
		printf("\n\tYour info\n\t=================================");
		printf("\n\tNames: %s", names);
		printf("\n\tCategory: %s", category);
		printf("\n\tYour cashpower number: %s", cashpower_input);
		printf("\n\tPrevious purchase month: |%s|", lastPurchaseMonth);
		printf("\n\tUnits this month: %d", monthPurchasedUnits);
		printf("\n\t=================================\n\tAmount of money: ");
		scanf("%d", &input_amount);
	}
}