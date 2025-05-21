#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1
struct Node {
int key;
int color;
struct Node *left, *right, *parent;
};
struct Node* createNode(int key) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->key = key;
newNode->color = RED;
newNode->left = newNode->right = newNode->parent = NULL;
return newNode;
}
void rotateLeft(struct Node **root, struct Node *x) {
struct Node *y = x->right;
x->right = y->left;
if (y->left != NULL)
y->left->parent = x;
y->parent = x->parent;
if (x->parent == NULL)
*root = y;
else if (x == x->parent->left)
x->parent->left = y;
else
x->parent->right = y;
y->left = x;
x->parent = y;
}
void rotateRight(struct Node **root, struct Node *x) {
struct Node *y = x->left;
x->left = y->right;
if (y->right != NULL)
y->right->parent = x;
y->parent = x->parent;
if (x->parent == NULL)
*root = y;
else if (x == x->parent->right)
x->parent->right = y;
else
x->parent->left = y;
y->right = x;
x->parent = y;
}
void fixViolation(struct Node **root, struct Node *z) {
struct Node *parent_z = NULL;
struct Node *grand_parent_z = NULL;
while ((z != *root) && (z
->color == RED) &&
(z->parent->color == RED)) {
parent_z = z->parent;
grand_parent_z = z->parent->parent;
if (parent_z == grand_parent_z->left) {
struct Node *uncle_z = grand_parent_z->right;
if (uncle_z != NULL && uncle_z->color == RED) {
grand_parent_z->color = RED;
parent_z->color = BLACK;
uncle_z->color = BLACK;
z = grand_parent_z;
} 
else {
if (z == parent_z->right) {
rotateLeft(root, parent_z);
z = parent_z;
parent_z = z->parent;
}

rotateRight(root, grand_parent_z);
int temp = parent_z->color;
parent_z->color = grand_parent_z->color;
grand_parent_z->color = temp;
z = parent_z;
}
} else {
struct Node *uncle_z = grand_parent_z->left;
if ((uncle_z != NULL) && (uncle_z->color == RED)) {
grand_parent_z->color = RED;
parent_z->color = BLACK;
uncle_z->color = BLACK;
z = grand_parent_z;
} 
else {
if (z == parent_z->left) {
rotateRight(root, parent_z);
z = parent_z;
parent_z = z->parent;
}

rotateLeft(root, grand_parent_z);
int temp = parent_z->color;
parent_z->color = grand_parent_z->color;
grand_parent_z->color = temp;
z = parent_z;}}}
(*root)->color = BLACK;}
void insert(struct Node **root, int key) {
struct Node *z = createNode(key);
struct Node *y = NULL;
struct Node *x = *root;
while (x != NULL) {
y = x;
if (z->key < x->key)
x = x->left;
else
x = x->right;
}
z->parent = y;
if (y == NULL)
*root = z;
else if (z->key < y->key)
y->left = z;
else
y->right = z;
fixViolation(root, z);
}

void inorderTraversal(struct Node *root) {
if (root == NULL) return;
inorderTraversal(root->left);
printf("%d ", root->key);
inorderTraversal(root->right);
}

void preorder(struct Node *root)
{
    if(root)
    {
        printf("%d ",root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root)
{
    if(root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->key);
    }
}

int main() 
{
struct Node *root = NULL;
insert(&root, 3);
insert(&root, 21);
insert(&root, 32);
insert(&root, 15);
printf("Inorder traversal of the constructed Red-Black tree is: \n");
inorderTraversal(root);
printf("\nPreorder traversal of the constructed Red-Black tree is: \n");
preorder(root);
printf("\nPostorder traversal of the constructed Red-Black tree is: \n");
postorder(root);
printf("\n");
return 0;
}