// E.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 110;
ll n, arr[MAX_N], dp[MAX_N][MAX_N][MAX_N];
char str[MAX_N];

ll dfs(int st, int ed, int pre)
{
    if (ed - st <= 0)
        return 0;
    if (ed - st == 1)
        return arr[pre];
    ll &ans = dp[st][ed][pre];
    if (ans != 0)
        return ans;
    ans = arr[pre] + dfs(st + 1, ed, 1);
    for (int i = st + 1; i < ed; i++)
        if (str[i] == str[st])
            ans = max(ans, dfs(st + 1, i, 1) + dfs(i, ed, pre + 1));
    return ans;
}

int main()
{
    scanf("%lld%s", &n, str);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    printf("%lld", dfs(0, n, 1));
    return 0;
}