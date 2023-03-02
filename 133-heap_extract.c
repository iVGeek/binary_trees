#include "binary_trees.h"

/* This function builds a Max Binary Heap tree from an array */
heap_t *array_to_heap(int *array, size_t size)
{
    /* Check for null pointer and empty array */
    if (array == NULL || size == 0)
        return NULL;

    /* Allocate memory for the new heap */
    heap_t *heap = malloc(sizeof(heap_t));
    if (heap == NULL)
        return NULL;

    /* Initialize the heap */
    heap->size = size;
    heap->data = malloc(size * sizeof(int));
    if (heap->data == NULL)
    {
        free(heap);
        return NULL;
    }

    /* Copy the array into the heap */
    for (size_t i = 0; i < size; i++)
        heap->data[i] = array[i];

    /* Build the heap */
    for (int i = (heap->size - 2) / 2; i >= 0; i--)
        heapify(heap, i);

    /* Return a pointer to the root node of the created binary heap */
    return heap;
}
