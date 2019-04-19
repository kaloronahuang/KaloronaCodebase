// P1370.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 2000, mod = 998244353;
int n, arr[MAX_N], head[MAX_N], dp[MAX_N];
vector<int> mapping;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), mapping.push_back(arr[i]);
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(mapping.begin(), mapping.end(), arr[i]) - mapping.begin() + 1;
    head[arr[n]] = n, dp[n] = 2;
    for (int i = n - 1; i >= 1; i--)
    {
        dp[i] = (dp[i + 1] * 2 % mod + 2) % mod;
        if (head[arr[i]])
            dp[i] = (dp[i] - dp[head[arr[i]] + 1] - 1 + mod) % mod;
        head[arr[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + dp[i]) % mod;
    printf("%d", ans);
    return 0;
}