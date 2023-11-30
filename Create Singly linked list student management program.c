#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student {
    int id;
    char name[50];
    int semester;
    struct Student* next;
};

// Function to create a new student node
struct Student* createStudent(int id, const char* name, int semester) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->semester = semester;
    newStudent->next = NULL;
    return newStudent;
}

// Function to insert a student at the beginning of the linked list
void insertStudent(struct Student** head, int id, const char* name, int semester) {
    struct Student* newStudent = createStudent(id, name, semester);
    newStudent->next = *head;
    *head = newStudent;
}

// Function to delete a student node based on student ID
void deleteStudent(struct Student** head, int id) {
    struct Student* current = *head;
    struct Student* prev = NULL;

    // Traverse the list to find the node with the specified ID
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // If the node is found, delete it
    if (current != NULL) {
        if (prev == NULL) {
            // If the node is at the beginning of the list
            *head = current->next;
        } else {
            // If the node is in the middle or end of the list
            prev->next = current->next;
        }

        free(current);
        printf("Student with ID %d deleted successfully!\n", id);
    } else {
        printf("Student with ID %d not found. Deletion failed.\n", id);
    }
}

// Function to display all students in the linked list
void displayStudents(struct Student* head) {
    printf("Student List:\n");
    while (head != NULL) {
        printf("ID: %d, Name: %s, Semester: %d\n", head->id, head->name, head->semester);
        head = head->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the linked list
void freeList(struct Student* head) {
    while (head != NULL) {
        struct Student* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Student* head = NULL;
    int choice, id, semester;
    char name[50];

    do {
        printf("\n1. Insert Student\n");
        printf("2. Delete Student\n");
        printf("3. Display Students\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &id);
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter semester: ");
                scanf("%d", &semester);
                insertStudent(&head, id, name, semester);
                break;
            case 2:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(&head, id);
                break;
            case 3:
                displayStudents(head);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    // Free allocated memory
    freeList(head);

    return 0;
}
