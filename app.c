#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float getUnits(char category[], float amount, float totalUnits);
long int generateToken();
int getNoOfTokens();
char *provideToken();
int deleteToken();
typedef struct token
{
	char tok[21];
	char flag[8];
} token;

int main()
{
	FILE *fp;
	fp = fopen("userdata.csv", "a");
	char customerName[50];
	char customerCategory[50];
	char firstTimeToBuy[10];
	int cashPowerNo;
	int amount, i;
	float recentUnits;

	printf("Enter your name: ");
	gets(customerName);
	printf("\n1. residential\n");
	printf("2. non_residential\n");
	printf("3. telecom_towers\n");
	printf("4. water_treatment\n");
	printf("5. hotels\n");
	printf("6. health_facilities\n");
	printf("7. broadcasters\n");
	printf("8. data_centers\n\n");
	printf("Copy paste your category: ");
	scanf("%s", customerCategory);

	printf("Enter the amount:");
	scanf("%d", &amount);

	printf("Enter your cashpower number: ");
	scanf("%d", &cashPowerNo);

	printf("Is it your first time to buy power in this month(yes or no)?: ");
	scanf("%s", firstTimeToBuy);
	if (strcmp(firstTimeToBuy, "yes"))
	{
		printf("How many units did you buy? ");
		scanf("%f", &recentUnits);
	}

	if (fp == NULL)
	{
		printf("That file couldn't be opened for some reason!\n");
		system("pause");
		return 1;
	}

	fprintf(fp, "%s,%s,%d,%d\n", customerName, customerCategory, cashPowerNo, amount);
	fclose(fp);

	printf("\n--------ELECTRICITY PURCHASE SYSTEM---------");
	float units;
	units = getUnits(customerCategory, amount, recentUnits);

	FILE *tokenfp;
	char c;
	int count;

	if (count < 2)
	{
		generateToken();
	}
	count = getNoOfTokens();

	printf("\n\tCustomer name: %s: ", customerName);
	printf("\n\tCustomer category: %s: ", customerCategory);
	printf("\n\tPurchased Units: %.2f Kwh", units);
	// Provide token;
	printf("\n\tProvided Token: %s", provideToken());
	deleteToken();
	return 0;
}
int deleteToken()
{
	int lno = 0, ctr = 0;
	char ch;
	FILE *fptr1, *fptr2;
	char str[100], temp[] = "temp.txt";
	fptr1 = fopen("Unused.txt", "r");
	if (!fptr1)
	{
		printf(" File not found or unable to open the input file!!\n");
		return 0;
	}
	fptr2 = fopen(temp, "w"); // open the temporary file in write mode
	if (!fptr2)
	{
		printf("Unable to open a temporary file to write!!\n");
		fclose(fptr1);
		return 0;
	}
	lno++;
	// copy all contents to the temporary file except the specific line
	while (!feof(fptr1))
	{
		strcpy(str, "\0");
		fgets(str, 100, fptr1);
		if (!feof(fptr1))
		{
			ctr++;
			/* skip the line at given line number */
			if (ctr != lno)
			{
				fprintf(fptr2, "%s", str);
			}
		}
	}
	fclose(fptr1);
	fclose(fptr2);
	remove("Unused.txt");		 // remove the original file
	rename(temp, "Unused.txt"); // rename the temporary file to original name
						 /*------ Read the file ----------------*/
	fptr1 = fopen("Unused.txt", "r");
	ch = fgetc(fptr1);
	while (ch != EOF)
	{
		printf("%c", ch);
		ch = fgetc(fptr1);
	}
	fclose(fptr1);
}
char *provideToken()
{
	FILE *fp;
	FILE *usedfp;
	char *token = malloc(20);
	//open file in read more
	fp = fopen("temp.txt", "r");
	usedfp = fopen("Used.txt", "a+");
	if (fp == NULL)
	{
		printf("File \"%s\" does not exist!!!\n", fp);
	}
	fgets(token, 100, fp);
	fputs(token, usedfp);
	return token;
	//close the file
	fclose(fp);
}

int getNoOfTokens()
{
	FILE *fp;
	char ch;
	int linesCount = 0;
	//open file in read more
	fp = fopen("Unused.txt", "r");
	if (fp == NULL)
	{
		printf("File \"%s\" does not exist!!!\n", fp);
		return -1;
	}
	//read character by character and check for new line
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
			linesCount++;
	}
	//close the file
	fclose(fp);
	//return number of lines
	return linesCount;
}

long int generateToken()
{
	// Generate tokens
	FILE *tokensfp;
	int i, j;
	char list[10][20];

	if ((tokensfp = fopen("Unused.txt", "a+")) == NULL)
	{
		fprintf(stdout, "Can't open \"Unused\" file.\n");
		exit(1);
	}

	srand(time(NULL)); //initialize random seed
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 20; j++)
		{
			list[i][j] = rand() % 10; //random number between 0 and 9
			fprintf(tokensfp, "%d", list[i][j]);
		}
		fprintf(tokensfp, "\n");
	}

	if (fclose(tokensfp) != 0)
	{
		fprintf(stderr, "Error closing file\n");
	}
}

float getUnits(char category[], float amount, float totalUnits)
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
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
		return 0;
	}

	else if (strcmp(category, "non_residential") == 0)
	{
		int amountperUnit = 227;
		int amountperUnit2 = 255;
		int standardUnits = 100 - totalUnits;
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
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
	}

	else if (strcmp(category, "water_treatment") == 0)
	{
		float amountPerunit = 126;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
	}

	else if (strcmp(category, "telecom_towers") == 0)
	{
		float amountPerunit = 201;
		if (amount >= amountPerunit)
		{
			units = amount / amountPerunit;
			return units;
		}
		else
		{
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
	}

	else if (strcmp(category, "hotels") == 0)
	{
		int amountPerunit = 157;
		if (amount >= amountPerunit)
		{
			units = amount / amountPerunit;
			return units;
		}
		else
		{
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
	}
	else if (strcmp(category, "health_facilities") == 0)
	{
		int amountPerunit = 186;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
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
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
	}
	else if (strcmp(category, "data_centers") == 0)
	{
		int amountPerunit = 179;
		if (amount >= amountPerunit)
		{
			units = (amount / amountPerunit);
			return units;
		}
		else
		{
			printf("\n\tYou don't have enough money / Your inputs are invalid!");
			exit(-1);
		}
	}
}