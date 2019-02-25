// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 110;
int n, arr[MAX_N << 1];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    copy(arr + 1, arr + 1 + n, arr + 1 + n);
    reverse(arr + 1 + n, arr + 1 + 2 * n);
    for (int i = 1; i <= 2 * n; i++)
        if (i & 1)
            printf("%d ", arr[i]);
    return 0;
}