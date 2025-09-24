#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void concatenate(Node** X1, Node* X2) {
    if (*X1 == NULL) {
        *X1 = X2;
        return;
    }
    if (X2 == NULL) {
        return;
    }

    Node* temp = *X1;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = X2;
    X2->prev = temp;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* X1 = NULL;
    Node* X2 = NULL;

    append(&X1, 10);
    append(&X1, 20);
    append(&X1, 30);

    append(&X2, 40);
    append(&X2, 50);
    append(&X2, 60);

    printf("List X1 before concatenation: ");
    printList(X1);

    printf("List X2 before concatenation: ");
    printList(X2);

    concatenate(&X1, X2);

    printf("List X1 after concatenation: ");
    printList(X1);

    return 0;
}
