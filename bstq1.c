#include <stdio.h>
#include <stdlib.h>

typedef struct Node{

    struct Node * Left;
    struct Node * Right;
    int data;

}Node;

void inorderTraversal(Node * root){
    if(root == NULL)return;

    inorderTraversal((root)->Left);

    printf("%d" , (root)->data);

    inorderTraversal((root)->Right);



}

void  createNodes(Node ** root , int data){


    if(*root == NULL){
        Node * newNode = (Node *)malloc(sizeof(Node));
        newNode->Left = NULL;
        newNode ->Right = NULL;
        newNode->data = data;
        *root = newNode;
        return;
    }

    if(data < (*root)->data){
         createNodes(&(*root)->Left , data);
    }else{

        createNodes(&(*root)->Right , data);
    }





}


int main(){


    Node *root = NULL;

    createNodes(&root , 3);
    createNodes(&root , 1);
    createNodes(&root , 2);
    createNodes(&root , 5);
    createNodes(&root , 7);
    createNodes(&root , 10);
    createNodes(&root , 6);
    createNodes(&root , 11);
    createNodes(&root , 0);

    inorderTraversal(root);
    return 0;
}
