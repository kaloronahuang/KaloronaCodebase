// POJ1011.cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 70;
int n, arr[maxn], stcnt, len;
bool vis[maxn];
bool cmp(int a, int b) { return a > b; }
bool dfs(int st, int cab, int last)
{
    if (st > stcnt)
        return true;
    if (cab == len)
        return dfs(st + 1, 0, 1);
    int fail = 0;
    for (int i = last; i <= n; i++)
        if (fail != arr[i] && cab + arr[i] <= len && !vis[i])
        {
            vis[i] = true;
            if (dfs(st, cab + arr[i], i + 1))
                return true;
            fail = arr[i];
            vis[i] = false;
            if (cab == 0 || cab + arr[i] == len)
                return false;
        }
    return false;
}
int main()
{
    while (scanf("%d", &n) && n)
    {
        int mx_val = 0, sum = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i]), mx_val = max(mx_val, arr[i]), sum += arr[i];
        sort(arr + 1, arr + n + 1, cmp);
        for (len = mx_val; len <= sum; len++)
        {
            if (sum % len)
                continue;
            stcnt = sum / len;
            memset(vis, false, sizeof(vis));
            if (dfs(1, 0, 1))
                break;
        }
        printf("%d\n", len);
    }
    return 0;
}