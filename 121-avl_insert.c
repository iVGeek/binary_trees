#include "binary_trees.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct avl_node_s {
    int value;
    struct avl_node_s *left;
    struct avl_node_s *right;
    int height;
} avl_t;

// A utility function to get the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// A utility function to get the height of the tree
int height(avl_t *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
avl_t *rightRotate(avl_t *y)
{
    avl_t *x = y->left;
    avl_t *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
avl_t *leftRotate(avl_t *x)
{
    avl_t *y = x->right;
    avl_t *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(avl_t *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
avl_t *insert(avl_t *node, int value)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return (avl_t *)malloc(sizeof(avl_t));

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(avl_t *root)
{
    if (root != NULL) {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// A function to insert a value in an AVL Tree
avl_t *avl_insert(avl_t **tree, int value)
{
    // If tree is NULL, create a new node and return it
    if (tree == NULL)
        return NULL;

    // Insert the value into the tree
    *tree = insert(*tree, value);

    // Return the created node
    return *tree;
}
