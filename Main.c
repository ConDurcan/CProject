//Conor Durcan - G00435598


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

float Never_Stat = 0;
float Less_3_Stat = 0;
float Less_5_Stat = 0;
float More_5_Stat = 0;

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
    struct machine* NEXT; 
} machineT;

typedef struct credentials {
    char username[7];
    char password[7];
}credT;



void openFile(machineT** headPtr)
{
    FILE* filePtr;
    filePtr = fopen("fleet.txt", "r");
    if (filePtr == NULL)
    {
        printf("File not found, creating a new file\n");
        filePtr = fopen("fleet.txt", "w");
        if (filePtr == NULL) {
            printf("Error creating file!\n");
            return;
        }
        fclose(filePtr);
        return; 
    }

    char line[200]; // Buffer for reading lines

    while (fgets(line, sizeof(line), filePtr) != NULL) 
    {
        machineT* newNode = (machineT*)malloc(sizeof(machineT));
        if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            continue;
        }

        int result = sscanf(line, "%s %s %s %d %f %f %d %d %s %s %d %d",
            newNode->chasisnumber, newNode->make, newNode->model,
            &newNode->year, &newNode->cost, &newNode->value,
            &newNode->mileage, &newNode->nextservice,
            newNode->owner, newNode->owneremail,
            &newNode->type, &newNode->breakdowns);

        if (result != 12) { // Check if all 12 fields were read
            printf("Error reading file entry. Skipping.\n");
            free(newNode);
            continue;
        }

        
        newNode->NEXT = *headPtr;
        *headPtr = newNode;
    }

    fclose(filePtr);
}



// Function to save data to file
void saveToFile(machineT* headPtr)
{
    FILE* filePtr = fopen("fleet.txt", "w");
    if (filePtr == NULL)
    {
        printf("Error opening file for writing!\n");
        return;
    }

    machineT* temp = headPtr;
    while (temp != NULL)
    {
        fprintf(filePtr, "%s %s %s %d %.2f %.2f %d %d %s %s %d %d\n",
            temp->chasisnumber, temp->make, temp->model,
            temp->year, temp->cost, temp->value,
            temp->mileage, temp->nextservice,
            temp->owner, temp->owneremail,
            temp->type, temp->breakdowns);

        temp = temp->NEXT;
    }

    fclose(filePtr);
    printf("Data saved to fleet.txt\n");
}



// Helper function to display a machine's details
void displayMachine(machineT* machine)
{
    printf("Chasis number: %s\n", machine->chasisnumber);
    printf("Make: %s\n", machine->make);
    printf("Model: %s\n", machine->model);
    printf("Year: %d\n", machine->year);
    printf("Cost: %.2f\n", machine->cost);
    printf("Value: %.2f\n", machine->value);
    printf("Mileage: %d\n", machine->mileage);
    printf("Next service: %d\n", machine->nextservice);
    printf("Owner: %s\n", machine->owner);
    printf("Owner email: %s\n", machine->owneremail);

    if (machine->type == 0)
    {
        printf("Type: Car\n");
    }
    else if (machine->type == 1)
    {
        printf("Type: Truck\n");
    }
    else
    {
        printf("Type: Unknown\n");
    }

    if (machine->breakdowns == 1)
    {
        printf("Breakdowns: Never\n");
    }
    else if (machine->breakdowns == 2)
    {
        printf("Breakdowns: Less than 3 times\n");
    }
    else if (machine->breakdowns == 3)
    {
        printf("Breakdowns: Less than 5 times\n");
    }
    else if (machine->breakdowns == 4)
    {
        printf("Breakdowns: More than 5 times\n");
    }
    else
    {
        printf("Breakdowns: Unknown\n");
    }
    printf("----------------------------------------------\n");
}
//This is a function to copy a linked list as I found out option 8 was destroying the original list
machineT* copyList(machineT* originalHead) {
    machineT* newHead = NULL; 
    machineT* tail = NULL; 

    machineT* currentOriginal = originalHead; // Pointer to traverse the original list

    while (currentOriginal != NULL) {
        
        machineT* newNode = (machineT*)malloc(sizeof(machineT));
        if (newNode == NULL) {
            // Memory allocation failed during copy
            printf("Memory allocation failed during list copy!\n");
            return NULL; // Ruh Roh
        }

        
        
        strcpy(newNode->chasisnumber, currentOriginal->chasisnumber);
        strcpy(newNode->make, currentOriginal->make);
        strcpy(newNode->model, currentOriginal->model);
        newNode->year = currentOriginal->year;
        newNode->cost = currentOriginal->cost;
        newNode->value = currentOriginal->value; // Copy the value
        newNode->mileage = currentOriginal->mileage;
        newNode->nextservice = currentOriginal->nextservice;
        strcpy(newNode->owner, currentOriginal->owner);
        strcpy(newNode->owneremail, currentOriginal->owneremail);
        newNode->type = currentOriginal->type;
        newNode->breakdowns = currentOriginal->breakdowns;

        newNode->NEXT = NULL; 

        
        if (newHead == NULL) {
            // The new list is currently empty, this is the first node
            newHead = newNode;
            tail = newNode; 
        }
        else {
            // The new list is not empty, append the new node to the tail
            tail->NEXT = newNode;
            tail = newNode; 
        }

       
        currentOriginal = currentOriginal->NEXT;
    }
    return newHead; 
}


// Function to generate statistics
void generateStats(machineT* machine)
{
	int breakdownCount1 = 0;
	int breakdownCount2 = 0;
	int breakdownCount3 = 0;
	int breakdownCount4 = 0;
	int overallCount = 0; 
	int count = 0; 
	machineT* temp = machine;
	printf("Generating machine statistics...\n");
    while (temp != NULL)
    {
		if (temp->breakdowns == 1)
		{
			breakdownCount1++;
			overallCount++;
		}
		else if (temp->breakdowns == 2)
		{
			breakdownCount2++;
			overallCount++;
		}
		else if (temp->breakdowns == 3)
		{
			breakdownCount3++;
			overallCount++;
		}
        else if (temp->breakdowns == 4)
        {
            breakdownCount4++;
			overallCount++;
        }
		temp = temp->NEXT;
    }
	Never_Stat = (float)breakdownCount1 / overallCount * 100;
	Less_3_Stat = (float)breakdownCount2 / overallCount * 100;
	Less_5_Stat = (float)breakdownCount3 / overallCount * 100;
	More_5_Stat = (float)breakdownCount4 / overallCount * 100;
	printf("Total machines: %d\n", overallCount);
	printf("Breakdown percentage: Never: %.2f\n", Never_Stat);
	printf("Breakdown percentage: Less than 3 times: %.2f\n", Less_3_Stat);
	printf("Breakdown percentage: Less than 5 times: %.2f\n", Less_5_Stat);
	printf("Breakdown percentage: More than 5 times: %.2f\n", More_5_Stat);
	printf("--------------------------------------------------\n");
}



void deleteMachine(char chasisnumber[], machineT** headPtr)
{
    machineT* temp = *headPtr; 
    machineT* prevTemp = NULL;
   

    // Handle case where the list is empty
    if (temp == NULL) {
        printf("List is empty, cannot delete.\n");
        return;
    }

    
    if (strcmp(temp->chasisnumber, chasisnumber) == 0)
    {
        *headPtr = temp->NEXT; 
        free(temp);
        printf("Machine with chasis number %s deleted successfully.\n", chasisnumber);
        return; 
    }

    // Traverse the rest of the list
    prevTemp = temp;
    temp = temp->NEXT;

    while (temp != NULL)
    {
        if (strcmp(temp->chasisnumber, chasisnumber) == 0)
        {
            prevTemp->NEXT = temp->NEXT; // Bypass the node to be deleted
            free(temp);
            printf("Machine with chasis number %s deleted successfully.\n", chasisnumber);
            return; 
        }
        prevTemp = temp;
        temp = temp->NEXT;
    }

    // If the loop finishes, the node was not found
    printf("Machine with chasis number %s not found.\n", chasisnumber);
}

void hidePassword(char* password, int maxlength)
{
    int i = 0;
    char ch;
    while (1) {
        ch = _getch(); // Changed to _getch()
        if (ch == 13) { // If Enter key is pressed
            password[i] = '\0';
            break;
        }
        else if (ch == 8) { // If Backspace key is pressed
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (i < 6) { // Check if within password size limit
            password[i++] = ch;
            printf("*"); // Print asterisk instead of the actual character
        }
    }
}



void logIn()
{
	char username[7];
	char password[7];
    char storedUserName[7];
    char storedPassWord[7];
	int attempts = 0;
    credT* headPtr = NULL;
	printf("Welcome to the Fleet Management System!\n");
	printf("Please log in to continue.\n");
    FILE* filePtr = fopen("login.txt", "r");
	if (filePtr == NULL)
	{
		printf("Login file not found. Creating a new one...\n");
		filePtr = fopen("login.txt", "w");
        printf("NOTE: USERNAME AND PASSWORD ARE CAPPED AT 6 CHARACTERS\n\n");
        printf("NOTE: Password unobscured for initial entry\n");
		printf("Please enter a username: ");
		scanf("%s", username);
		printf("Please enter a password: ");
		scanf("%s", password);
		fprintf(filePtr, "%s %s", username, password);
		fclose(filePtr);
		return; // Exit after creating the file
	}
    headPtr = (credT*)malloc(sizeof(credT));
    if (fscanf(filePtr, "%s %s", headPtr->username, headPtr->password) != 2)
    {
        printf("Error reading credentials from login file.\n");
        fclose(filePtr);
        free(headPtr); // Free allocated memory
        exit(1);
    }
	while (attempts < 3)
	{
		printf("Enter username: ");
		scanf("%s", username);
		printf("Enter password: ");
		hidePassword(password, 6);

		if (strcmp(username, headPtr->username) == 0 && strcmp(password, headPtr->password) == 0)
		{
			printf("\nLogin successful!\n");
			return;
		}
		else
		{
			printf("Invalid username or password. Try again.\n");
			attempts++;
		}
	}

	printf("Too many failed attempts. Exiting...\n");
	exit(1);
}




int main() 
{
    machineT* headPtr = NULL;
    machineT* temp;
    machineT* prevTemp;
    machineT* newNode;
    int menuOption;
    int count = 0;
    char check[20];
    char username[6];
    char password[6];
    bool StatsGenerated = false; // Flag to check if stats have been generated

    openFile(&headPtr);
	logIn(); // Call the login function
    do
    {
        printf("\n===== Fleet Management System =====\n");
        printf("Enter 1 to add a machine\n");
        printf("Enter 2 to display all the machines\n");
        printf("Enter 3 to search for a specific chasis number\n");
        printf("Enter 4 to update a specific machine\n");  
		printf("Enter 5 to delete a specific machine\n");
        printf("Enter 6 to generate machine statistics\n");
        printf("Enter 7 to put all machine details into a report\n"); 
        printf("Enter 8 to list all machinery in order of value\n"); 
        printf("Enter -1 to exit\n");
        printf("--------------------------------------------------\n");
        scanf("%d", &menuOption);

        if (menuOption == 1)
        {
            newNode = (machineT*)malloc(sizeof(machineT));
            bool isUnique = false;
            if (newNode == NULL) {
                printf("Memory allocation failed!\n");
                continue;
            }

            printf("Please enter the chassis number\n");
            scanf("%s", newNode->chasisnumber);
			//Loop to check if the chassis number is unique
            do {
                isUnique = true;
                machineT* current = headPtr;

                while (current != NULL) {
                    if (strcmp(current->chasisnumber, newNode->chasisnumber) == 0) {
                        isUnique = false;
                        printf("Chassis number already exists. Please enter a different one.\n");
                        scanf("%s", newNode->chasisnumber);
                        break; // Exit the inner while loop to restart checking
                    }
                    current = current->NEXT;
                }
            } while (!isUnique);

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
            printf("Machine added successfully!\n");
        }
        
        else if (menuOption == 2)
        {
            if (headPtr == NULL) {
                printf("The list is empty. No machines to display.\n");
            }
            else {
                temp = headPtr;
                count = 1;

                printf("\n===== All Machines =====\n");
                while (temp != NULL)
                {
                    printf("Machine #%d\n", count++);
                    displayMachine(temp);
                    temp = temp->NEXT;
                }
            }
        }
        else if (menuOption == 3)
        {
            if (headPtr == NULL) {
                printf("The list is empty. No machines to search.\n");
                continue;
            }

            printf("What chasis number are you looking for? ");
            scanf("%s", check);  
            temp = headPtr;
            count = 1;
            int found = 0;

            while (temp != NULL)  // Check for NULL instead of infinite loop
            {
                if (strcmp(temp->chasisnumber, check) == 0)
                {
                    printf("Found %s at position %d in the list\n", check, count);  
                    displayMachine(temp);  
                    found = 1;
                    break;
                }
                temp = temp->NEXT;
                count++;
            }

            if (!found) {
                printf("Machine with chasis number %s not found in the list.\n", check);
            }
            count = 0;  // Reset count for next operation
        }
        else if (menuOption == 4)
        {
            if (headPtr == NULL) {
                printf("The list is empty. No machines to update.\n");
                continue;
            }

            printf("Enter the chasis number of the machine to update: ");
            scanf("%s", check);
            temp = headPtr;
            int found = 0;

            while (temp != NULL)
            {
                if (strcmp(temp->chasisnumber, check) == 0)
                {
                    printf("Machine found! Enter new details:\n");

                    printf("Please enter the make\n");
                    scanf("%s", temp->make);

                    printf("Please enter the model\n");
                    scanf("%s", temp->model);

                    printf("Please enter the year\n");
                    scanf("%d", &temp->year);

                    printf("Please enter the cost\n");
                    scanf("%f", &temp->cost);

                    printf("Please enter the value\n");
                    scanf("%f", &temp->value);

                    printf("Please enter the mileage\n");
                    scanf("%d", &temp->mileage);

                    printf("Please enter the next service\n");
                    scanf("%d", &temp->nextservice);

                    printf("Please enter the owner name\n");
                    scanf("%s", temp->owner);

                    printf("Please enter the owner email\n");
                    scanf("%s", temp->owneremail);

                    printf("Please enter the type of machine (0 for car, 1 for truck)\n");
                    scanf("%d", &temp->type);

                    printf("Please enter the number of breakdowns - 1. Never 2. Less than 3 times 3. Less than 5 times 4. More than 5 times\n");
                    scanf("%d", &temp->breakdowns);

                    printf("Machine updated successfully!\n");
                    found = 1;
                    break;
                }
                temp = temp->NEXT;
            }

            if (!found) {
                printf("Machine with chasis number %s not found in the list.\n", check);
            }
        }
        else if (menuOption == 5)
        {
			printf("Please enter the chasis number to delete: ");
			scanf("%s", check);

			deleteMachine(check, &headPtr); 
            }
        else if (menuOption == 6)
        {
			StatsGenerated = true; // For checking if stats have been generated for the report
			generateStats(headPtr);
		}
		else if (menuOption == 7)
		{
            temp = headPtr;
			printf("Generating report...\n");
			printf("Note: The report will only include correct statistics if they have been generated just before creating the report.\n");
            FILE* filePtr = fopen("report.txt", "w");
            temp = headPtr;

            while (temp != NULL)
            {
				fprintf(filePtr, "Chasis number: %s\n", temp->chasisnumber);
				fprintf(filePtr, "Make: %s\n", temp->make);
				fprintf(filePtr, "Model: %s\n", temp->model);
				fprintf(filePtr, "Year: %d\n", temp->year);
				fprintf(filePtr, "Cost: %.2f\n", temp->cost);
				fprintf(filePtr, "Value: %.2f\n", temp->value);
				fprintf(filePtr, "Mileage: %d\n", temp->mileage);
				fprintf(filePtr, "Next service: %d\n", temp->nextservice);
				fprintf(filePtr, "Owner: %s\n", temp->owner);
				fprintf(filePtr, "Owner email: %s\n", temp->owneremail);
				if (StatsGenerated = true)
				{
					fprintf(filePtr, "Breakdowns: Never: %.2f\n", Never_Stat);
					fprintf(filePtr, "Breakdowns: Less than 3 times: %.2f\n", Less_3_Stat);
					fprintf(filePtr, "Breakdowns: Less than 5 times: %.2f\n", Less_5_Stat);
					fprintf(filePtr, "Breakdowns: More than 5 times: %.2f\n", More_5_Stat);
				}
				fprintf(filePtr, "----------------------------------------------\n");
				temp = temp->NEXT; 
            }
            if (StatsGenerated == false)
            {
				printf("If you would like a report with statistics, please generate them first using menu option 6.\n");
            }
			printf("Report generated successfully! Check report.txt for details.\n");
			fclose(filePtr);
			}
		else if (menuOption == 8) 
		{
			printf("Sorting machines by value...\n");
            temp = copyList(headPtr);
			machineT* sortedList = NULL;
			machineT* originalList = headPtr;
			int leastvaluable = 0;
            int round = 1;
			// Loop to sort the machines by value 
			// This is to make sure the loop runs the same amount of times as the number of machines
            while (temp != NULL)
			{
				machineT* currentNode = temp;
				machineT* prevNode = NULL;
				machineT* minNode = temp;
				machineT* minPrev = NULL;
				//Loop in a loop to find the minimum node
				while (currentNode != NULL)
				{
                    //if the value of the current node is bigger than the minimum node this changes minNode to the currentNode
                    if (currentNode->value < minNode->value)
                    {
					    minNode = currentNode;
					    minPrev = prevNode;
                    }
				    prevNode = currentNode;
				    currentNode = currentNode->NEXT;
			    }
				
				//At the end of the loop the minimum node is the one with the least value
                if (minPrev == NULL)
                {
                    temp = minNode->NEXT; 
                }
                else
                {
                    minPrev->NEXT = minNode->NEXT; // Link the node before minNode to the node after minNode
                }
                minNode->NEXT = NULL; // Detach the removed minNode from the original list

				// Insert the minNode at the beginning of the sorted list
                if (sortedList == NULL)
                {
					sortedList = minNode; 
				}
                else
                {
                    minNode->NEXT = sortedList; 
                    sortedList = minNode; 
                }

            }

			// Print the sorted list
			printf("\n===== Machines Sorted by Value =====\n");
            while (sortedList != NULL)
            {
                printf("Chasis number: %s Value:%.2f\n",sortedList->chasisnumber, sortedList->value);
				sortedList = sortedList->NEXT;
            }
			printf("\n----------------------------------------------\n");
			free(sortedList); 

        }
    } while (menuOption != -1);
	// Save the data to file before exiting
     saveToFile(headPtr);
    // Free all memory before exiting
    temp = headPtr;
    while (temp != NULL)
    {
        machineT* next = temp->NEXT;
        free(temp);
        temp = next;
    }
   
    printf("Program terminated. Thank you for using Fleet Management System!\n");
    return 0;
}