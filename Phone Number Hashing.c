#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

struct Employee {
    char phone[15];
    char name[50];
    // Add other information as needed
};

struct Node {
    struct Employee data;
    struct Node *next;
};

struct HashTable {
    struct Node *table[TABLE_SIZE];
};

// Hash function to convert phone numbers to an index
int hashFunction(const char *phone) {
    int sum = 0;
    for (int i = 0; phone[i] != '\0'; i++) {
        sum += phone[i];
    }
    return sum % TABLE_SIZE;
}

// Function to insert a record into the hash table
void insertRecord(struct HashTable *hashTable, struct Employee emp) {
    int index = hashFunction(emp.phone);

    // Create a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = emp;
    newNode->next = NULL;

    // Insert the node at the beginning of the linked list at the calculated index
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        newNode->next = hashTable->table[index];
        hashTable->table[index] = newNode;
    }

    printf("Record inserted successfully!\n");
}

// Function to search for a record in the hash table
void searchRecord(struct HashTable *hashTable, const char *phone) {
    int index = hashFunction(phone);
    struct Node *current = hashTable->table[index];

    // Traverse the linked list to find the record
    while (current != NULL) {
        if (strcmp(current->data.phone, phone) == 0) {
            printf("Record found:\n");
            printf("Phone: %s\n", current->data.phone);
            printf("Name: %s\n", current->data.name);
            return;
        }
        current = current->next;
    }

    printf("Record not found for phone number %s\n", phone);
}

// Function to delete a record from the hash table
void deleteRecord(struct HashTable *hashTable, const char *phone) {
    int index = hashFunction(phone);
    struct Node *current = hashTable->table[index];
    struct Node *prev = NULL;

    // Traverse the linked list to find and delete the record
    while (current != NULL) {
        if (strcmp(current->data.phone, phone) == 0) {
            if (prev == NULL) {
                // If the record is at the beginning of the list
                hashTable->table[index] = current->next;
            } else {
                // If the record is in the middle or end of the list
                prev->next = current->next;
            }

            free(current);
            printf("Record deleted successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Record not found for phone number %s\n", phone);
}

// Function to display all records in the hash table
void displayAllRecords(struct HashTable *hashTable) {
    printf("Current records in the hash table:\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node *current = hashTable->table[i];

        while (current != NULL) {
            printf("Phone: %s, Name: %s\n", current->data.phone, current->data.name);
            current = current->next;
        }
    }
}

int main() {
    struct HashTable hashTable;

    // Initialize the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable.table[i] = NULL;
    }

    int choice;
    do {
        printf("\n1. Insert Record\n");
        printf("2. Search Record\n");
        printf("3. Delete Record\n");
        printf("4. Display All Records\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Employee emp;
                printf("Enter phone number: ");
                scanf("%s", emp.phone);
                printf("Enter name: ");
                scanf("%s", emp.name);
                insertRecord(&hashTable, emp);
                break;
            }
            case 2: {
                char phone[15];
                printf("Enter phone number to search: ");
                scanf("%s", phone);
                searchRecord(&hashTable, phone);
                break;
            }
            case 3: {
                char phone[15];
                printf("Enter phone number to delete: ");
                scanf("%s", phone);
                deleteRecord(&hashTable, phone);
                break;
            }
            case 4:
                displayAllRecords(&hashTable);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
