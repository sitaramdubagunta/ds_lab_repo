
#include<stdio.h>
#include<stdlib.h>
struct Node
{
int data;
struct Node *next;
};
void insertBefore(struct Node** head, int value, int before);
void insertAfter(struct Node** head, int value, int after);
void deleteNode(struct Node** head, int value);
void traverse(struct Node* head);
void reverseList(struct Node** head);
void sortList(struct Node** head);
void deleteAlternateNodes(struct Node** head);
void insertIntoSorted(struct Node** head, int value);

int main()
{
struct Node* head = NULL;
int choice,value,key;
while (1) {
printf("\n--- Singly Linked List Menu ---\n");
printf("0. Insert at beginning\n");
printf("1. Insert before a specified element\n");
printf("2. Insert after a specified element\n");
printf("3. Delete a specified element\n");
printf("4. Traverse the list\n");
printf("5. Reverse the list\n");
printf("6. Sort the list\n");
printf("7. Delete every alternate node\n");
printf("8. Insert into a sorted linked list\n");
printf("9. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice)
{
case 0:
{
printf("Enter value to insert at beginning: ");
scanf("%d", &value);
insertAtBeginning(&head, value);
break;
}

case 1:
{
printf("Enter value to insert: ");
scanf("%d", &value);
printf("Insert before which value? ");
scanf("%d", &key);
insertBefore(&head, value, key);
break;
}

case 2:
{
printf("Enter value to insert: ");
scanf("%d", &value);
printf("Insert after which value? ");
scanf("%d", &key);
insertAfter(&head, value, key);
break;
}

case 3:
{
printf("Enter value to delete: ");
scanf("%d", &value);
deleteNode(&head, value);
break;
}

case 4:
{
traverse(head);
break;
}

case 5:
{
reverseList(&head);
break;
}

case 6:
{
sortList(&head);
break;
}

case 7:
{
deleteAlternateNodes(&head);
break;
}

case 8:
{
printf("Enter value to insert into sorted list: ");
scanf("%d", &value);
insertIntoSorted(&head, value);
break;
}

case 9:
{
exit(0);
break;
}
}
}
return 0;
}

void insertAtBeginning(struct Node** head, int value) {
struct Node* newNode = malloc(sizeof(struct Node));
if (!newNode) {
printf("Memory allocation failed\n");
return;
}
newNode->data = value;
newNode->next = *head;
*head = newNode;
}

void insertBefore(struct Node** head, int value, int before)
{
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->data = value;

if (*head == NULL) {
printf("List is empty.\n");
free(newNode);
return;
}
if ((*head)->data == before) {
newNode->next = *head;
*head = newNode;
return;
}

struct Node* prev = NULL;
struct Node* current = *head;

while (current != NULL && current->data != before) {
prev = current;
current = current->next;
}

if (current == NULL) {
printf("Element %d not found.\n", before);
free(newNode);
return;
}
newNode->next = current;
prev->next = newNode;
}

void insertAfter(struct Node** head, int value, int after) {
    struct Node* current = *head;

    while (current != NULL && current->data != after) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Element %d not found.\n", after);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = value;
    newNode->next = current->next;
    current->next = newNode;
}

void deleteNode(struct Node** head, int value) {
struct Node* temp = *head;
struct Node* prev = NULL;

while (temp != NULL && temp->data != value) {
prev = temp;
temp = temp->next;
}

if (temp == NULL) {
printf("Element %d not found.\n", value);
return;
}
if (prev == NULL) {
*head = temp->next;
} else
{
prev->next = temp->next;
}

free(temp);
printf("Element %d deleted.\n", value);
}

void traverse(struct Node* head) {
if (head == NULL) {
printf("List is empty.\n");
return;
}

struct Node* temp = head;
printf("List: ");
while (temp != NULL) {
printf("%d -> ", temp->data);
temp = temp->next;
}
printf("NULL\n");
}

void reverseList(struct Node** head) {
struct Node* prev = NULL;
struct Node* current = *head;
struct Node* next = NULL;
while (current != NULL) {
next = current->next;
current->next = prev;
prev = current;
current = next;
}

*head = prev;
printf("List reversed.\n");
}

void sortList(struct Node** head) {
if (*head == NULL) return;
int swapped;
struct Node *ptr1, *lptr = NULL;

do {
swapped = 0;
ptr1 = *head;

while (ptr1->next != lptr) {
if (ptr1->data > ptr1->next->data) {
int temp = ptr1->data;
ptr1->data = ptr1->next->data;
ptr1->next->data = temp;
swapped = 1;
}
ptr1 = ptr1->next;
}
lptr = ptr1;
}
while (swapped);
printf("List sorted.\n");
}


void deleteAlternateNodes(struct Node** head) {
if (*head == NULL)
return;
struct Node* current = *head;
struct Node* temp;

while (current != NULL && current->next != NULL) {
temp = current->next;
current->next = temp->next;
free(temp);
current = current->next;
}

printf("Alternate nodes deleted.\n");
}

void insertIntoSorted(struct Node** head, int value) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->data = value;
newNode->next = NULL;

if (*head == NULL || (*head)->data >= value) {
newNode->next = *head;
*head = newNode;
return;
}

struct Node* current = *head;
while (current->next != NULL && current->next->data < value) {
current = current->next;
}

newNode->next = current->next;
current->next = newNode;
}

