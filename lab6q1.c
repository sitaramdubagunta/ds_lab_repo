
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* First = NULL;
Node* Last = NULL;


void display() {
    if (First == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = First;
    printf("List: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != First);
    printf("\n");
}


void insertEnd(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;

    if (First == NULL) {
        First = newNode;
        Last = newNode;
        newNode->next = First;
    } else {
        Last->next = newNode;
        Last = newNode;
        Last->next = First;
    }
    printf("Inserted %d at the end.\n", value);
    display();
}


void deleteBeginning() {
    if (First == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    if (First == Last) {
        printf("Deleted %d from the beginning.\n", First->data);
        free(First);
        First = NULL;
        Last = NULL;
    } else {
        Node* temp = First;
        printf("Deleted %d from the beginning.\n", temp->data);
        First = First->next;
        Last->next = First;
        free(temp);
    }
    display();
}


void deleteEnd() {
    if (First == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    if (First == Last) {
        printf("Deleted %d from the end.\n", Last->data);
        free(Last);
        First = NULL;
        Last = NULL;
    } else {
        Node* temp = First;

        while (temp->next != Last) {
            temp = temp->next;
        }
        printf("Deleted %d from the end.\n", Last->data);
        temp->next = First;
        free(Last);
        Last = temp;
    }
    display();
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Circular Singly Linked List Operations ---\n");
        printf("1. Insert at end\n");
        printf("2. Delete from beginning\n");
        printf("3. Delete from end\n");
        printf("4. Display list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertEnd(value);
                break;
            case 2:
                deleteBeginning();
                break;
            case 3:
                deleteEnd();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
