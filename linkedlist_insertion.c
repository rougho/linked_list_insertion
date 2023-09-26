// Rouhollah Ghobadinezhad
// Algorithm and Data Structure
// HW2/Q2

// Task: Write a program that reads data from a file named BST-BCS-11a_Students.txt and inserts 
// them into a data structure made up of linked lists in a sorted manner with respect to your requirement
//  in the table below. Then print the whole data to the screen. 




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

struct address {
    int number;
    char streetName[30];
    char cityName[15];
    char country[15];
};

struct a_person {
    char name[25];
    char lname[25];
    int age;
    double weight;
    char gender;
    double grade;
    struct address person_address;
    struct a_person* nextPtr;
};


char * removeSpacesFromStr(char *string)
{
    int non_space_count = 0;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[non_space_count] = string[i];
            non_space_count++;
        }
    }
    string[non_space_count] = '\0';
    return string;
}


void insertNode(struct a_person** head, struct a_person* newNode) {
    if (*head == NULL || strcmp(newNode->person_address.country, (*head)->person_address.country) < 0) {
        newNode->nextPtr = *head;
        *head = newNode;
    } else {
        struct a_person* current = *head;
        while (current->nextPtr != NULL && strcmp(newNode->person_address.country, current->nextPtr->person_address.country) >= 0) {
            current = current->nextPtr;
        }
        newNode->nextPtr = current->nextPtr;
        current->nextPtr = newNode;
    }
}


void displayList(struct a_person* head,int tracker) {
    struct a_person* current = head;
    int count = 1;
    printf("============================================================================================\n");
    printf("========== rougho - According to Country name (ascending order) ==========\n");
    printf("============================================================================================\n");
    printf("||\t-> Number of records available in list: %d\n", tracker);
    printf("=========================================================\n");
    while (current != NULL) {
        printf("||-> Person No. %d:\n", count);
        printf("||\tName: %s\n||\tLastName: %s\n", current->name, current->lname);
        printf("||\tAge: %d\n", current->age);
        printf("||\tWeight: %.2f\n", current->weight);
        printf("||\tGender: %c\n", current->gender);
        printf("||\tGrade: %.2f\n", current->grade);
        printf("||\tAddress:\n||\t\tStreet and No: %s %d\n||\t\tCity:%s\n||\t\tCountry:%s\n",current->person_address.streetName,
               current->person_address.number,
               current->person_address.cityName,
               current->person_address.country);
        printf("=========================================================\n");
        current = current->nextPtr;
        count++;
    }
}


void freeList(struct a_person* head) {
    struct a_person* current = head;
    while (current != NULL) {
        struct a_person* temp = current;
        current = current->nextPtr;
        free(temp);
    }
}



int main() {
    struct a_person* head = NULL;
    FILE* fptr;
    fptr = fopen("data.txt", "r");
    if (!fptr) {
        printf("readfile err");
        return 1;
    }

    char buffer[MAX_LENGTH];
    int tracker = 0;
    int isFirstLine = 1; // tracker to indicate if it's the first line

    while (fgets(buffer, MAX_LENGTH, fptr)) {
        if (isFirstLine) {
            isFirstLine = 0;
            continue; // skip the first line
        }

        struct a_person* temp = malloc(sizeof(struct a_person));
        if (temp == NULL) {
            printf("Memory allocation err\n");
            return 1;
        }

        char* token = strtok(buffer, ",");
        int tokenCounter = 0;

        while (token != NULL) {
            char *endPtr = NULL;
            switch (tokenCounter) {
                case 0:
                    strncpy(temp->name, token, sizeof(temp->name));
                    token = strtok(NULL, ",");
                    break;
                case 1:
                    strncpy(temp->lname, token, sizeof(temp->lname));
                    token = strtok(NULL, ",");
                    break;
                case 2:
                    for (int i = 0; i < sizeof(token); ++i) {
                        if (token[i] == 'M' || token[i] == 'F') {
                            temp->gender = token[i];
                            token = strtok(NULL, ",");
                        }
                    }
                    break;
                case 3:
                    // better to use strtol for integers and strtof for floating-point instead of atoi and atof (atoi & atof will not report conversion errors)
                    //temp->age = strtol(token,&endPtr,10);
                    temp->age = atoi(token);
                    token = strtok(NULL, ",");
                    break;
                case 4:
                    //temp->weight = strtof(token,&endPtr);
                    temp->weight = atof(token);
                    token = strtok(NULL, ",");
                    break;
                case 5:
                    //temp->grade = strtof(token,&endPtr);
                    temp->grade = atof(token);
                    token = strtok(NULL, " ");
                    break;
                case 6:
                    //temp->person_address.number = strtol(token,&endPtr,10);
                    temp->person_address.number = atof(token);
                    token = strtok(NULL, ",");
                    break;
                case 7:
                    strncpy(temp->person_address.streetName, token, sizeof(temp->person_address.streetName));
                    token = strtok(NULL, ",");
                    break;
                case 8:
                    strncpy(temp->person_address.cityName, token, sizeof(temp->person_address.cityName));
                    token = strtok(NULL, ".");
                    break;
                case 9:
                    strncpy(temp->person_address.country, token, sizeof(temp->person_address.country));
                    token = strtok(NULL, "\n");
                    break;
                default:
                    break;
            }
            tokenCounter++;
        }

        temp->nextPtr = NULL;
        insertNode(&head, temp);
        tracker++;

    }

    displayList(head,tracker);
    fclose(fptr);
    freeList(head);

    return 0;
}
