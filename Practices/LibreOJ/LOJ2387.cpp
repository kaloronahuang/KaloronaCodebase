// LOJ2387.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7, inv2 = (mod + 1) >> 1;

typedef long long ll;

int n, yi[MAX_N], lft[MAX_N], rig[MAX_N], row[MAX_N], col[MAX_N], pre[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d", &x, &y), yi[x] = y;
    int val = n;
    for (int i = 0; i < n; i++)
        val = min(val, yi[i] + 1), lft[i + 1] = val;
    val = 0;
    for (int i = n - 1; i >= 0; i--)
        val = max(val, yi[i]), rig[i] = val;

    for (int i = 1, ptr = n - 1; i < n; i++)
    {
        while (i > rig[ptr])
            ptr--;
        col[i] = ptr + 1, row[i] = lft[i] - 1;
    }

    int ans = 0;
    for (int i = 1; i < n; i++)
        pre[i] = (0LL + pre[i - 1] + 1LL * col[i] * i % mod) % mod;
    for (int i = 1; i < n; i++)
        ans = (0LL + ans + (pre[rig[i]] + mod - pre[lft[i] - 1]) % mod) % mod;
    // printf("%d\n", ans);
    for (int i = 1; i < n; i++)
        ans = (0LL + ans + mod - 1LL * i * (lft[i] + rig[i]) % mod * (rig[i] - lft[i] + 1) % mod * inv2 % mod) % mod;
    // printf("%d\n", ans);
    for (int i = 1; i < n; i++)
        ans = (0LL + ans + 1LL * row[i] * i % mod * (rig[i] - lft[i] + 1) % mod) % mod;
    // printf("%d\n", ans);
    for (int i = 1; i < n; i++)
        pre[i] = (0LL + pre[i - 1] + col[i]) % mod;
    for (int i = 1; i < n; i++)
        ans = (0LL + ans + mod - 1LL * row[i] * ((0LL + pre[rig[i]] + mod - pre[lft[i] - 1]) % mod) % mod) % mod;
    printf("%d\n", ans);
    return 0;
}