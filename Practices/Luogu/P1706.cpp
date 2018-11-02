// P1706.cpp
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main()
{
    int arr[10], n;
    cin >> n;
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
    do
    {
        for (int i = 0; i < n; i++)
            cout << setw(5) << arr[i];
        cout << endl;
    } while (next_permutation(arr, arr + n));
    return 0;
}