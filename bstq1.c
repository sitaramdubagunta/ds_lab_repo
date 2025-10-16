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
void postorderTraversal(Node * root){
    if(root == NULL)return;
    postorderTraversal((root)->Left);
    postorderTraversal((root)->Right);

    printf("%d" ,(root)->data);
}

void preorderTraversal(Node * root){
    if(root == NULL)return;

    printf("%d" , root->data);

    preorderTraversal(root->Left);
    preorderTraversal(root->Right);


}

void PrintParent(Node * root , int targetdata){
    if(root == NULL)return;


    if((root->Left && root->Left->data == targetdata) || (root->Right && root->Right->data == targetdata)){


        printf("the parent of %d is %d" , targetdata  , root->data);
    }

    PrintParent(root->Left , targetdata);
    PrintParent(root->Right , targetdata);



}
int PrintAncestor(Node * root , int targetdata){

    if(root == NULL)return 0;

    if(root->data == targetdata ) return 1;

    if((PrintAncestor(root->Left , targetdata) )|| (PrintAncestor(root->Right , targetdata))){
        printf("%d ",root->data);

        return 1;
    }
    return 0;





}

int DepthofTree(Node * root){

    if(root == NULL)return 0;

    int left = DepthofTree(root->Left);
    int right = DepthofTree(root->Right);


    return( left > right ? left : right )+1;


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

    if(data < (*root)->data){root->Left && root->Left->data == targetdata)
         createNodes(&(*root
)->Left , data);
    }else{

        createNodes(&(*root)->Right , data);
    }





}


int main(){


    Node *root = NULL;
  /*
    createNodes(&root , 3);
    createNodes(&root , 1);
    createNodes(&root , 2);
    createNodes(&root , 5);
    createNodes(&root , 7);
    createNodes(&root , 10);
    createNodes(&root , 6);
    createNodes(&root , 11);
    createNodes(&root , 0);
    printf("%d" , DepthofTree(root));
    */;
    //inorderTraversal(root);


    //PrintParent(root , 11);


    createNodes(&root ,6);
    createNodes(&root , 4);
    createNodes(&root , 10);
    createNodes(&root , 2);
    createNodes(&root , 0);
    createNodes(&root , 1);
    PrintAncestor(root  , 2);
    return 0;
}
