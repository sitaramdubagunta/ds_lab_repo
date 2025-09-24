
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;


void insertAtRear(int value);
void deleteFromRear();
void insertAtPosition(int value, int position);
void deleteFromPosition(int position);
void insertAfterValue(int value, int after);
void insertBeforeValue(int value, int before);
void traverseForward();
void traverseBackward();

int main() {
    int choice, value, position, key;

    while (1) {
        printf("\n--- Doubly Linked List Menu ---\n");
        printf("1. Insert at rear end\n");
        printf("2. Delete from rear end\n");
        printf("3. Insert at given position\n");
        printf("4. Delete from given position\n");
        printf("5. Insert after a specific value\n");
        printf("6. Insert before a specific value\n");
        printf("7. Traverse forward\n");
        printf("8. Traverse backward\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertAtRear(value);
                break;

            case 2:
                deleteFromRear();
                break;

            case 3:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter position to insert at (starting from 1): ");
                scanf("%d", &position);
                insertAtPosition(value, position);
                break;

            case 4:
                printf("Enter position to delete from (starting from 1): ");
                scanf("%d", &position);
                deleteFromPosition(position);
                break;

            case 5:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Insert after value: ");
                scanf("%d", &key);
                insertAfterValue(value, key);
                break;

            case 6:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Insert before value: ");
                scanf("%d", &key);
                insertBeforeValue(value, key);
                break;

            case 7:
                traverseForward();
                break;

            case 8:
                traverseBackward();
                break;

            case 9:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}


void insertAtRear(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
    printf("Inserted %d at rear.\n", value);
}

void deleteFromRear() {
    if (!tail) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct Node* temp = tail;
    printf("Deleting %d from rear.\n", temp->data);

    if (tail->prev) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        head = tail = NULL;
    }
    free(temp);
}

void insertAtPosition(int value, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 1) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (!newNode) {
            printf("Memory allocation failed!\n");
            return;
        }
        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = head;

        if (head)
            head->prev = newNode;
        else
            tail = newNode;

        head = newNode;
        printf("Inserted %d at position %d.\n", value, position);
        return;
    }

    struct Node* current = head;
    int i = 1;
    while (current && i < position - 1) {
        current = current->next;
        i++;
    }

    if (!current) {
        printf("Position out of bounds!\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next)
        current->next->prev = newNode;
    else
        tail = newNode;

    current->next = newNode;
    printf("Inserted %d at position %d.\n", value, position);
}

void deleteFromPosition(int position) {
    if (position < 1 || !head) {
        printf("Invalid position or empty list.\n");
        return;
    }

    struct Node* current = head;
    int i = 1;
    while (current && i < position) {
        current = current->next;
        i++;
    }

    if (!current) {
        printf("Position out of bounds.\n");
        return;
    }

    printf("Deleting %d from position %d.\n", current->data, position);

    if (current->prev)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next)
        current->next->prev = current->prev;
    else
        tail = current->prev;

    free(current);
}

void insertAfterValue(int value, int after) {
    struct Node* current = head;

    while (current && current->data != after) {
        current = current->next;
    }

    if (!current) {
        printf("Element %d not found.\n", after);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next)
        current->next->prev = newNode;
    else
        tail = newNode;

    current->next = newNode;
    printf("Inserted %d after %d.\n", value, after);
}

void insertBeforeValue(int value, int before) {
    struct Node* current = head;

    while (current && current->data != before) {
        current = current->next;
    }

    if (!current) {
        printf("Element %d not found.\n", before);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;

    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev)
        current->prev->next = newNode;
    else
        head = newNode;

    current->prev = newNode;
    printf("Inserted %d before %d.\n", value, before);
}

void traverseForward() {
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = head;
    printf("Forward traversal: ");
    while (current) {
        printf("%d", current->data);
        if (current->next)
            printf(" <-> ");
        current = current->next;
    }
    printf("\n");
}

void traverseBackward() {
    if (!tail) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = tail;
    printf("Backward traversal: ");
    while (current) {
        printf("%d", current->data);
        if (current->prev)
            printf(" <-> ");
        current = current->prev;
    }
    printf("\n");
}
