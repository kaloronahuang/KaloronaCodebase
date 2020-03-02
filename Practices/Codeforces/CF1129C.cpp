// CF1129C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, mod = 1e9 + 7, hash_mod = 1e7, bitnum = 133;

typedef unsigned long long ull;

int n, str[MAX_N], head[hash_mod], current, dp[MAX_N][MAX_N];
ull pre[MAX_N], hashpow[MAX_N];
map<int, bool> checker;

struct edge
{
    ull to;
    int nxt;
} edges[MAX_N * MAX_N];

ull getHash(int l, int r) { return (pre[r] - pre[l - 1] * hashpow[r - l + 1]); }

void addpath(int src, ull dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    checker[2370594] = true, checker[2388150] = true;
    checker[4740919] = true, checker[4740920] = true;
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &str[i]);
    for (int i = hashpow[0] = 1; i <= n; i++)
        hashpow[i] = hashpow[i - 1] * bitnum;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] * bitnum + str[i] + 1;
    for (int i = 1; i <= n + 1; i++)
        dp[0][i] = 1;
    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            dp[len][i] = dp[len - 1][i + 1];
            if (len >= 2)
                dp[len][i] = (0LL + dp[len][i] + dp[len - 2][i + 2]) % mod;
            if (len >= 3)
                dp[len][i] = (0LL + dp[len][i] + dp[len - 3][i + 3]) % mod;
            if (len >= 4)
                dp[len][i] = (0LL + dp[len][i] + 1LL * (!checker[getHash(i, i + 3)]) * dp[len - 4][i + 4]) % mod;
        }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            ull val = getHash(j, i);
            bool duplicate = false;
            for (int e = head[val % hash_mod]; e != -1 && !duplicate; e = edges[e].nxt)
                if (edges[e].to == val)
                    duplicate = true;
            if (!duplicate)
                ans = (0LL + ans + dp[i - j + 1][j]) % mod, addpath(val % hash_mod, val);
        }
        printf("%d\n", ans);
    }
    return 0;
}