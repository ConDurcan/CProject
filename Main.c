#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct machine
{
	char chasisnumber[20];
	char make[30];
	char model[25];
	int year;
	float cost;
	float value;
	int mileage;
	int nextservice;
	char owner[30];
	char owneremail[30];
	int type;
	int breakdowns;
	struct node* NEXT;
}machineT;

void openFile(machineT* headPtr)
{
	FILE* filePtr;
	filePtr = fopen("machines.txt", "a");
	if (filePtr == NULL)
	{
		filePtr = fopen("machines.txt", "w");
	}

	while (!feof(filePtr))
	{
		machineT* newNode = (machineT*)malloc(sizeof(machineT));
		fscanf(filePtr, "%s %s %s %d %f %f %d %d %s %s %d %d", newNode->chasisnumber, newNode->make, newNode->model, &newNode->year, &newNode->cost, &newNode->value, &newNode->mileage, &newNode->nextservice, newNode->owner, newNode->owneremail, &newNode->type, &newNode->breakdowns);
		newNode->NEXT = headPtr;
		headPtr = newNode;
	}
	fclose(filePtr);
}

void main()
{
	machineT* headPtr = NULL;
	machineT* temp;
	machineT* prevTemp;
	machineT* newNode;
	int menuOption;
	int count = 0;
	int check = 0;
	char username[6];
	char password[6];

	openFile(headPtr);

	printf("Enter 1 to add a node at the start\n");
	printf("Enter 2 to add a node at the end\n");
	printf("Enter 3 to display all the nodes\n");
	printf("Enter 4 to search for a specific chasis number\n");
	scanf("%d", &menuOption);

	if (menuOption == 1)
	{
		newNode = (machineT*)malloc(sizeof(machineT));

		printf("Please enter the chasis number\n");
		scanf("%s", newNode->chasisnumber);

		printf("Please enter the make\n");
		scanf("%s", newNode->make);

		printf("Please enter the model\n");
		scanf("%s", newNode->model);

		printf("Please enter the year\n");
		scanf("%d", &newNode->year);

		printf("Please enter the cost\n");
		scanf("%f", &newNode->cost);

		printf("Please enter the value\n");
		scanf("%f", &newNode->value);

		printf("Please enter the mileage\n");
		scanf("%d", &newNode->mileage);

		printf("Please enter the next service\n");
		scanf("%d", &newNode->nextservice);

		printf("Please enter the owner name\n");
		scanf("%s", newNode->owner);

		printf("Please enter the owner email\n");
		scanf("%s", newNode->owneremail);

		printf("Please enter the type of machine (0 for car, 1 for truck)\n");
		scanf("%d", &newNode->type);

		printf("Please enter the number of breakdowns - 1. Never 2. Less than 3 times 3. Less than 5 times 4. More than 5 times\n");
		scanf("%d", &newNode->breakdowns);

		newNode->NEXT = headPtr;
		headPtr = newNode;

	}
	else if (menuOption == 2)
	{
		temp = headPtr;

		while (temp->NEXT != NULL)
		{
			temp = temp->NEXT;
		}

		newNode = (machineT*)malloc(sizeof(machineT));

		printf("Please enter the chasis number\n");
		scanf("%s", newNode->chasisnumber);

		printf("Please enter the make\n");
		scanf("%s", newNode->make);

		printf("Please enter the model\n");
		scanf("%s", newNode->model);

		printf("Please enter the year\n");
		scanf("%d", &newNode->year);

		printf("Please enter the cost\n");
		scanf("%f", &newNode->cost);

		printf("Please enter the value\n");
		scanf("%f", &newNode->value);

		printf("Please enter the mileage\n");
		scanf("%d", &newNode->mileage);

		printf("Please enter the next service\n");
		scanf("%d", &newNode->nextservice);

		printf("Please enter the owner name\n");
		scanf("%s", newNode->owner);

		printf("Please enter the owner email\n");
		scanf("%s", newNode->owneremail);

		printf("Please enter the type of machine (0 for car, 1 for truck)\n");
		scanf("%d", &newNode->type);

		printf("Please enter the number of breakdowns - 1. Never 2. Less than 3 times 3. Less than 5 times 4. More than 5 times\n");
		scanf("%d", &newNode->breakdowns);

		newNode->NEXT = NULL;
		temp->NEXT = newNode;
		

	}
	else if (menuOption == 3)
	{
		temp = headPtr;

		while (temp != NULL)
		{
			printf("Chasis number: %s\n", temp->chasisnumber);
			printf("Make: %s\n", temp->make);
			printf("Model: %s\n", temp->model);
			printf("Year: %d\n", temp->year);
			printf("Cost: %.2f\n", temp->cost);
			printf("Value: %.2f\n", temp->value);
			printf("Mileage: %d\n", temp->mileage);
			printf("Next service: %d\n", temp->nextservice);
			printf("Owner: %s\n", temp->owner);
			printf("Owner email: %s\n", temp->owneremail);
			if (temp->type == 0)
			{
				printf("Type: Car\n");
			}
			else if (temp->type == 1)
			{
				printf("Type: Truck\n");
			}
			else
			{
				printf("Type: Unknown\n");
			}
			if (temp->breakdowns == 1)
			{
				printf("Breakdowns: Never\n");
			}
			else if (temp->breakdowns == 2)
			{
				printf("Breakdowns: Less than 3 times\n");
			}
			else if (temp->breakdowns == 3)
			{
				printf("Breakdowns: Less than 5 times\n");
			}
			else if (temp->breakdowns == 4)
			{
				printf("Breakdowns: More than 5 times\n");
			}
			else
			{
				printf("Breakdowns: Unknown\n");
			}
			printf("----------------------------------------------");
			temp = temp->NEXT;
		}
	}
	else if(menuOption == 4)
	{
		printf("What chasis number are you looking for? ");
		scanf("%d", &check);
		temp = headPtr;

		while (1)
		{
			if (temp->chasisnumber == check)
			{
				printf("Found %d at %d in the list\n", check, count + 1);
				printf("Chasis number: %s\n", temp->chasisnumber);
				printf("Make: %s\n", temp->make);
				printf("Model: %s\n", temp->model);
				printf("Year: %d\n", temp->year);
				printf("Cost: %.2f\n", temp->cost);
				printf("Value: %.2f\n", temp->value);
				printf("Mileage: %d\n", temp->mileage);
				printf("Next service: %d\n", temp->nextservice);
				printf("Owner: %s\n", temp->owner);
				printf("Owner email: %s\n", temp->owneremail);
				if (temp->type == 0)
				{
					printf("Type: Car\n");
				}
				else if (temp->type == 1)
				{
					printf("Type: Truck\n");
				}
				else
				{
					printf("Type: Unknown\n");
				}
				if (temp->breakdowns == 1)
				{
					printf("Breakdowns: Never\n");
				}
				else if (temp->breakdowns == 2)
				{
					printf("Breakdowns: Less than 3 times\n");
				}
				else if (temp->breakdowns == 3)
				{
					printf("Breakdowns: Less than 5 times\n");
				}
				else if (temp->breakdowns == 4)
				{
					printf("Breakdowns: More than 5 times\n");
				}
				else
				{
					printf("Breakdowns: Unknown\n");
				}
				break;
				count = 0;
			}
			temp = temp->NEXT;
			count++;
			if (temp->NEXT == NULL)
			{
				printf("Element not in list\n");
				break;
				count = 0;
			}
		}
	}
	
	
}


/*
*/