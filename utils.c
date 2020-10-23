#include <stdio.h>
#include <stdlib.h>
struct TreeNode
{
    char data;                     // character
    unsigned freq;                 // frequency of the character
    struct TreeNode *left, *right; // left and right children
};

struct Tree
{
    unsigned size;
    unsigned capacity;
    struct TreeNode **array;
};

// assigns new node to character and their freq
struct TreeNode *addNode(char data, unsigned freq)
{
    struct TreeNode *temp = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// create a heap of some capacity
struct Tree *makeHeap(unsigned capacity)
{
    struct Tree *minHeap = (struct Tree *)malloc(sizeof(struct Tree));

    // current size is 0
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct TreeNode **)malloc(minHeap->capacity * sizeof(struct TreeNode *));
    return minHeap;
}

// swapping 2 nodes
void swap(struct TreeNode **a, struct TreeNode **b)
{
    struct TreeNode *t = *a;
    *a = *b;
    *b = t;
}

// standard minHeapify function
void Heapify(struct Tree *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swap(&minHeap->array[smallest],
             &minHeap->array[idx]);
        Heapify(minHeap, smallest);
    }
}

// A utility function to check if size of heap is 1 or not
int isSingle(struct Tree *minHeap)
{
    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct TreeNode *extractMin(struct Tree *minHeap)
{
    struct TreeNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    Heapify(minHeap, 0);
    return temp;
}

// insert a new node to Min Heap
void insertMinHeap(struct Tree *minHeap, struct TreeNode *minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

//wrapper class for minHeapify function
void buildMinHeap(struct Tree *minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        Heapify(minHeap, i);
}
// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// Utility function to check if this node is leaf
int isLeafNode(struct TreeNode *root)
{
    return !(root->left) && !(root->right);
}