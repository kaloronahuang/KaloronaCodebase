// HeapSort.cpp
// Page 84 on Introduction of Algorithm;

// Header part;
#include <iostream>

using namespace std;

// utils;

int parent(int i)
{
    return (int)(i / 2);
}

int left(int i)
{
    return (i * 2);
}

int right(int i)
{
    return (i * 2 + 1);
}

// functions;

// Function:max_heapify
// A    :   the binary heap;
// i    :   the root to maxiumize;
// n    :   the number of the elements;
void max_heapify(int *A, int i, int n)
{
    // Get two children's positions;
    int l_pos = left(i);
    int r_pos = right(i);
    // Create a variable to indicate the next one;
    int largest_pos = i;
    // To judge whether to move up the left;
    if (l_pos < n && A[l_pos] > A[i])
        largest_pos = l_pos;
    // Then judge one on right;
    if (r_pos < n && A[r_pos] > A[largest_pos])
        largest_pos = r_pos;
    if (largest_pos != i)
    {
        // Time to exchange;
        swap(A[largest_pos], A[i]);
        // Then to judge whether the root is largest in the sub-tree;
        max_heapify(A, largest_pos, n);
    }
}

// Note:
// This function means to max the sub-trees to get the whole sorted;
void build_max_heap(int *A, int n)
{
    // Max the sub roots;
    for (int i = (int)(n / 2); i > 0; i--)
        max_heapify(A, i, n);
}

void heapSort(int *A, int n)
{
    // Build the largest heap;
    build_max_heap(A, n);
    // Then split the root element to the tail,
    // and build max heap on the [0,(tail-1)]. Repeatedly.
    for (int i = n; i > 1; i--)
    {
        swap(A[1], A[i]);
        max_heapify(A, 1, i);
    }
}

void set_increasing_key(int *A, int i, int key)
{
    if (A[i] > key)
        return;
    A[i] = key;
    // TODO;
}