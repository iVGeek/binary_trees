#include "binary_trees.h"

// C Function to Extract Root Node of a Max Binary Heap
int heap_extract(heap_t **root) 
{
    // Check if root is NULL
    if (!(*root)) 
        return 0;
    
    // Store the value of root node
    int max = (*root)->data;
    
    // Get the last level-order node of the heap
    heap_t *lastNode = *root;
    while (lastNode->left) 
        lastNode = lastNode->left;
    
    // Swap the root node with lastLevel node
    int temp = (*root)->data;
    (*root)->data = lastNode->data;
    lastNode->data = temp;
    
    // Get the parent of last level node
    heap_t *parent = lastNode->parent;
    
    // Set the appropriate child of parent as NULL
    if (parent->left == lastNode) 
        parent->left = NULL;
    else
        parent->right = NULL;
    
    // Free the last level node
    free(lastNode);
    
    // Rebuild the heap if necessary
    heap_t *curr = *root;
    while (curr->left || curr->right) 
    {
        // If both children exist, swap with the larger child
        if (curr->left && curr->right) 
        {
            if (curr->left->data > curr->right->data) 
            {
                int temp = curr->data;
                curr->data = curr->left->data;
                curr->left->data = temp;
                curr = curr->left;
            } 
            else 
            {
                int temp = curr->data;
                curr->data = curr->right->data;
                curr->right->data = temp;
                curr = curr->right;
            }
        } 
        // If only left child exists, swap with it
        else if (curr->left) 
        {
            int temp = curr->data;
            curr->data = curr->left->data;
            curr->left->data = temp;
            curr = curr->left;
        } 
        // If only right child exists, swap with it
        else 
        {
            int temp = curr->data;
            curr->data = curr->right->data;
            curr->right->data = temp;
            curr = curr->right;
        }
    }
    
    // Return the value stored in root node
    return max;
}
