// InsertionSort.cpp
// Page 10 on Introduction of Algorithm;

// Header part;
#include <iostream>

using namespace std;

// Analysis on insertion sort:
// Complication :   O(n^2);

// Function to do insertion sort;
// arr  :   the array waiting for being sorted;
// n    :   the number of the elements;
void insertionSort(int *arr, int n)
{
    // Picking up the number from the second element;
    for (int i = 1; i < n; i++)
        // Compare it with the previous elements;
        for (int j = i - 1; j > -1; j--)
            // Compare these;
            if (arr[i] < arr[j])
                // Swap these;
                swap(arr[i], arr[j]);
}