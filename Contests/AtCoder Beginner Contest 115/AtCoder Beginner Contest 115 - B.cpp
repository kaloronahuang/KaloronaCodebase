// AtCoder Beginner Contest 115 - B.cpp
#include <iostream>
#include <algorithm>
using namespace std;
int arr[100], N;

int main()
{
    int sum = 0, mx = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i], sum += arr[i], mx = max(mx, arr[i]);
    sum -= mx / 2;
    cout << sum;
    return 0;
}