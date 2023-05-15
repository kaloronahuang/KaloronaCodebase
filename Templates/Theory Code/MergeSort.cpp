// MergeSort.cpp
// Page 16 on Introduction of Algorithm;

// Header part;
#include <iostream>
#include <cmath>

using namespace std;

// Analysis on merge sort;
// Complication:    O(n log n)

// Extra note:
// 3 steps:
//      1.If n = 1, done;
//      2.Recursively do on A[0,ceil(n/2)];
//      3.Merge them;

// Function merge:
// arr  :   data array;
// start:   the start pos;
// mid  :   the middle pos;
// end  :   the end pos;
void merge(int *arr, int start, int mid, int end)
{
    // Prepare for new data array;
    int *left = new int[mid - start + 2];
    int *right = new int[end - mid + 1];
    // The pos marker;
    int i = start, j = mid + 1;
    // Put data to data pools;
    for (; i <= mid; i++)
        left[i - start] = arr[i];
    for (; j <= end; j++)
        right[j - mid - 1] = arr[j];
    // Protection on array;
    left[mid - start + 1] = INT32_MAX;
    right[end - mid] = INT32_MAX;
    // Reset markers;
    i = 0;
    j = 0;
    // Merge from 2 arraies;
    for (int cnt = start; cnt <= end; cnt++)
    {
        // Judge to put data;
        if (right[i] > left[j])
        {
            arr[cnt] = left[j];
            // Marker up;
            j++;
        }
        else
        {
            arr[cnt] = right[i];
            // Marker up;
            i++;
        }
    }
    // Dispose data pools;
    delete [] left;
    delete [] right;
}

// Function mergeSort:
// arr  :   array to sort;
// start:   start pos;
// end  :   end pos;
void mergeSort(int *arr, int start, int end)
{
    // Exit for recursion;
    if (start == end)
        return;
    // Spliting them;
    // Left;
    mergeSort(arr, start, (int)((start + end) / 2));
    // Right;
    mergeSort(arr, ((int)(start + end) / 2) + 1, end);
    // Merge them;
    merge(arr, start, (int)((start + end) / 2), end);
}