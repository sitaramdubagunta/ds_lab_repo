
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int c, int e) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(Node** head, int c, int e) {
    Node* newNode = createNode(c, e);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* curr = *head;
    while (curr && curr->exp > e)
        curr = curr->next;
    if (curr == NULL) {
        Node* tail = *head;
        while (tail->next) tail = tail->next;
        tail->next = newNode;
        newNode->prev = tail;
    }
    else if (curr->exp == e) {
        curr->coeff += c;
        free(newNode);
    }
    else if (curr == *head) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
    else {
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
}

Node* addPolynomials(Node* p1, Node* p2) {
    Node* sum = NULL;
    Node* t1 = p1;
    Node* t2 = p2;

    while (t1 && t2) {
        if (t1->exp > t2->exp) {
            insertTerm(&sum, t1->coeff, t1->exp);
            t1 = t1->next;
        }
        else if (t2->exp > t1->exp) {
            insertTerm(&sum, t2->coeff, t2->exp);
            t2 = t2->next;
        }
        else {
            int c = t1->coeff + t2->coeff;
            if (c != 0)
                insertTerm(&sum, c, t1->exp);
            t1 = t1->next;
            t2 = t2->next;
        }
    }
    while (t1) {
        insertTerm(&sum, t1->coeff, t1->exp);
        t1 = t1->next;
    }
    while (t2) {
        insertTerm(&sum, t2->coeff, t2->exp);
        t2 = t2->next;
    }
    return sum;
}

void display(Node* head) {
    Node* curr = head;
    while (curr) {
        printf("%dx^%d", curr->coeff, curr->exp);
        if (curr->next)
            printf(" + ");
        curr = curr->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* curr = head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    insertTerm(&poly1, 5, 3);
    insertTerm(&poly1, 4, 2);
    insertTerm(&poly1, 2, 0);

    insertTerm(&poly2, 3, 4);
    insertTerm(&poly2, 2, 3);
    insertTerm(&poly2, 7, 0);

    Node* sum = addPolynomials(poly1, poly2);

    display(poly1);
    display(poly2);
    display(sum);

    freeList(poly1);
    freeList(poly2);
    freeList(sum);

    return 0;
}
