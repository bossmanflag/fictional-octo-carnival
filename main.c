#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
// max height of the huffman tree
#define MAX_TREE_HT 10
int currindex = 0;

//struct lookupitem table[6];
int table[6][6];
char letters[6];
int tops[6];

// makes a heap of the data[]
struct Tree *createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct Tree *minHeap = makeHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = addNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Huffman tree travesal Algorithm
// Step 1: Create a min heap of capacity equal to size. Initially, there are  modes equal to size.
// Step 2: Extract the two minimum freq items from min heap
// Step 3: Create a new internal node with frequency equal to the sum of the two nodes frequencies.
//         Make the two extracted node as left and right children of this new node.
//         Add this node to the min heap '$' is a special value for internal nodes, not used
// Step 4: The remaining node is the root node and the tree is complete.
struct TreeNode *buildHuffmanTree(char data[], int freq[], int size)
{
    struct TreeNode *left, *right, *top;

    struct Tree *minHeap = createAndBuildMinHeap(data, freq, size);
    // loop till size of heap is not 1
    while (!isSingle(minHeap))
    {

        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = addNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Recursively prints the huffman code of each letter. It uses arr[] to store codes
void encode(struct TreeNode *root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        encode(root->left, arr, top + 1);
    }
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        encode(root->right, arr, top + 1);
    }

    // If this is a leaf node, then  it contains one of the input characters, print the character and its code from arr[]
    if (isLeafNode(root))
    {
        printf("%c: ", root->data);
        printArr(arr, top);
        printf("Size of the %c : %d\n", root->data, (int)(top * sizeof(int)));

        for (int i = 0; i < top; i++)
        {
            table[currindex][i] = arr[i];
        }
        letters[currindex] = root->data;
        tops[currindex] = top;
        currindex++;
    }
}

// Driver program to test above functions
int main()
{
    char carr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    printf("Consider a string of the following frequency\n");
    int sizeofthestring = 0;
    for (int i = 0; i < 6; i++)
    {
        printf("Size of all %c = %d bits \n", carr[i], sizeof(carr[i]) * 8 * freq[i]);
        sizeofthestring += sizeof(carr[i]) * 8 * freq[i];
    }
    printf("In total, this means total space occupied by the string is %d bits\n", sizeofthestring);

    int size = sizeof(carr) / sizeof(carr[0]);
    struct TreeNode *root = buildHuffmanTree(carr, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    encode(root, arr, top);
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%c ", letters[i]);
    //     printArr(table[i], tops[i]);
    //
    return 0;
}
