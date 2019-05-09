// CF1156C.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 2000;

int n, k, arr[MAX_N], ans;
bool vis[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    int l = 0, r = n / 2, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        bool flag = true;
        for (int i = 1; i <= mid; i++)
            if (arr[n - mid + i] - arr[i] < k)
            {
                flag = false;
                break;
            }
        if (flag)
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}