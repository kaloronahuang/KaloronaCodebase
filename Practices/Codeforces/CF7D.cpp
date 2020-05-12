// CF7D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAX_N = 5e6 + 200, base = 133;

int n, dp[MAX_N];
char str[MAX_N];
ull pre[MAX_N], pw[MAX_N], rpre[MAX_N];

ull getHash(int l, int r) { return pre[r] - pre[l - 1] * pw[r - l + 1]; }

ull getHashRev(int l, int r) { return rpre[l] - rpre[r + 1] * pw[r - l + 1]; }

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = pw[0] = 1; i <= n; i++)
        pw[i] = pw[i - 1] * base, pre[i] = pre[i - 1] * base + str[i] - 'A' + 1;
    for (int i = n; i >= 1; i--)
        rpre[i] = rpre[i + 1] * base + str[i] - 'A' + 1;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int len = (i >> 1);
        if (getHash(1, len) == getHashRev(i - len + 1, i))
            dp[i] = dp[len] + 1;
        ans += dp[i];
    }
    printf("%lld\n", ans);
    return 0;
}