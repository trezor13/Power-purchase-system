#include "customerstruct.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tokenstruct
{
	char content[21];
	char status[8];
} tokenstruct;

float getUnits(char category[], float amount, int unitsSoFar);

void main()
{
	char cashpower_input[12], names[100], category[100], lastPurchaseMonth[12];
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
	float input_amount, monthPurchasedUnits;
	int i = 0, j = 0, cashpower_valid = 0, final_units, n, customer_index;
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
		printf("\n\tYour info\n\t=================================");
		printf("\n\tNames: %s", names);
		printf("\n\tCategory: %s", category);
		printf("\n\tYour cashpower number: %s", cashpower_input);
		printf("\n\tPrevious purchase month: %s", lastPurchaseMonth);
		printf("\n\tUnits bought in %s: %.2f", lastPurchaseMonth, monthPurchasedUnits);
		printf("\n\t=================================\n\tAmount of money: ");
		scanf("%f", &input_amount);
		float units;
		units = getUnits(category, input_amount, monthPurchasedUnits);
		if (strcmp(lastPurchaseMonth, currentMon))
		{
			FILE *fp3;
			fp3 = fopen("customer_info_binary.csv", "w");
			strcpy(customersArr[customer_index].lastPurchaseMonth, currentMon);
			customersArr[customer_index].monthPurchasedUnits = 0;

			for (i = 0; i < n; i++)
				fwrite(&customersArr[i], sizeof(customer), 1, fp3);
			fclose(fp3);
		}
		FILE *fp4;
		fp4 = fopen("customer_info_binary.csv", "w");
		customersArr[customer_index].monthPurchasedUnits += units;

		for (i = 0; i < n; i++)
			fwrite(&customersArr[i], sizeof(customer), 1, fp4);
		fclose(fp4);
		tokenstruct t1, storedTokens[100], tokens_arr2[1];
		FILE *fp5;
		fp5 = fopen("tokens.csv", "r");
		i = 0;
		while (fread(&t1, sizeof(tokenstruct), 1, fp5))
		{
			storedTokens[i] = t1;
			i++;
		}
		fclose(fp5);
	generateToken:
		j = 0;
		/* Initializes random number generator */
		time_t t;
		FILE *fp6;
		srand((unsigned)time(&t));
		fp6 = fopen("tokens.csv", "w");
		j = rand() % i;
		if (!strcmp(storedTokens[j].status, "used"))
			goto generateToken;
		strcpy(storedTokens[j].status, "used");
		int d;
		for (d = 0; d < i; d++)
		{
			tokens_arr2[0] = storedTokens[d];
			fwrite(tokens_arr2, sizeof(tokenstruct), 1, fp6);
		}
		fclose(fp6);
		printf("\n\t=================================\n\tPurchased Units: %.2f Kwh", units);
		printf("\n\tToken to use: %11s\n", storedTokens[j].content);
	}
}

float getUnits(char category[], float amount, int unitsSoFar)
{
	float units;

	if (strcmp(category, "residential") == 0)
	{
		if (amount >= 89)
		{
			float round1 = amount / 89;
			if (round1 <= 15)
			{
				units = round1;
				return units;
			}
			else
			{
				round1 = 15;
				float remaining_amount_round1 = amount - 1335;
				float round2 = remaining_amount_round1 / 212;
				if (round2 <= 35)
				{
					float total_interval2 = round1 + round2;
					units = total_interval2;
					return units;
				}
				else
				{
					round2 = 35;
					float remaining_amount_round2 = amount - (1335 + 7420);
					float round3 = remaining_amount_round2 / 249;
					float total_interval3 = round1 + round2 + round3;
					units = total_interval3;
					return units;
				}
			}
		}
		else
		{
			printf("\n\tThe Entered Amount is less than the minmum allowed or you entered invalid characters2.");
			exit(-1);
		}
		return 0;
	}

	else if (strcmp(category, "nonresidential") == 0)
	{
		int amountperUnit = 227;
		int amountperUnit2 = 255;
		int standardUnits = 100 - unitsSoFar;
		int standardAmount = amountperUnit * standardUnits;
		if ((amount >= amountperUnit))
		{
			if ((amount <= standardAmount))
			{
				units = amount / amountperUnit;
				return units;
			}
			else
			{
				int firstCase = amount - standardAmount;
				units = (standardAmount / amountperUnit) + (firstCase / amountperUnit2);
				return units;
			}
		}
		else
		{
			printf("\n\tThe Entered Amount is less than the minmum allowed or you entered invalid characters1.");
			exit(-1);
		}
	}

	else if (strcmp(category, "waterTreatment") == 0)
	{
		float amountPerunit = 126;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tThe amount is less than the min amount allowed or you entered invalid characters");
			exit(-1);
		}
	}

	else if (strcmp(category, "telecomeTowers") == 0)
	{
		float amountPerunit = 201;
		if (amount >= amountPerunit)
		{
			units = amount / amountPerunit;
			return units;
		}
		else
		{
			printf("\n\tThe amount is less than the min amount allowed or you entered invalid characters");
			exit(-1);
		}
	}

	else if (strcmp(category, "hotel") == 0)
	{
		int amountPerunit = 157;
		if (amount >= amountPerunit)
		{
			units = amount / amountPerunit;
			return units;
		}
		else
		{
			printf("\n\tThe amount is less than the min amount allowed or you entered invalid characters");
			exit(-1);
		}
	}
	else if (strcmp(category, "health") == 0)
	{
		int amountPerunit = 186;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tThe amount is less than the min amount allowed or you entered invalid characters");
			exit(-1);
		}
	}
	else if (strcmp(category, "broadcasters") == 0)
	{
		int amountPerunit = 192;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tThe amount is less than the min amount allowed or you entered invalid characters");
			exit(-1);
		}
	}
	else if (strcmp(category, "dataCenters") == 0)
	{
		int amountPerunit = 179;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tThe amount is less than the min amount allowed or you entered invalid characters");
			exit(-1);
		}
	}
}
