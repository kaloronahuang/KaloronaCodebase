// P1091.cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1000;
const int INF = 0x7fffffff;

int n;
int arr[maxn];

int solve(int pos)
{
    // get the increasing until the pos;
    int cursorI = 1;
    int cursorD = 1;

    int lis[maxn];
    lis[1] = arr[1];
    for (int i = 2; i <= pos; i++)
        if (lis[cursorI] < arr[i])
            lis[++cursorI] = arr[i];
        else
            *(lower_bound(lis + 1, lis + cursorI, arr[i])) = arr[i];

    int lds[maxn];
    lds[1] = arr[n];
    for (int i = n - 1; i >= pos; i--)
        if (lds[cursorD] < arr[i])
            lds[++cursorD] = arr[i];
        else
            *(lower_bound(lds + 1, lds + cursorD, arr[i])) = arr[i];
    return cursorI + cursorD;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, solve(i));
    cout << n - ans + 1;
    return 0;
}