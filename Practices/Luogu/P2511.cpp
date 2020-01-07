// P2511.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_M = 1010, mod = 10007;

int n, m, li[MAX_N], dp[2][MAX_N], pre[MAX_N];
int prefix[MAX_N];

bool check(int mid)
{
    int cnt = 0, acc = 0;
    for (int i = 1; i <= n; i++)
        if (acc + li[i] > mid)
            cnt++, acc = li[i];
        else
            acc += li[i];
    if (acc != 0)
        cnt++;
    return cnt <= m;
}

int main()
{
    scanf("%d%d", &n, &m), m++;
    int mx_len = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &li[i]), pre[i] = pre[i - 1] + li[i], mx_len = max(mx_len, li[i]);
    int l = mx_len, r = pre[n], res, sum = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    for (int i = 1; i <= n; i++)
        dp[1][i] = (pre[i] <= res) % mod, prefix[i] = (prefix[i - 1] + dp[1][i]) % mod;
    sum = dp[1][n];
    for (int group = 2; group <= m; group++)
    {
        memset(dp[group & 1], 0, sizeof(dp[group & 1]));
        for (int i = group, ptr = 0; i <= n; i++)
        {
            while (pre[i] - pre[ptr] > res)
                ptr++;
            dp[group & 1][i] = (prefix[i - 1] + mod - (ptr == 0 ? 0 : prefix[ptr - 1])) % mod;
        }
        sum = (sum + dp[group & 1][n]) % mod;
        for (int i = 0; i <= n; i++)
            prefix[i] = ((i == 0 ? 0 : prefix[i - 1]) + dp[group & 1][i]) % mod;
    }
    printf("%d %d\n", res, sum);
    return 0;
}