// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 20, mod = 998244353;

int b[MAX_N], c[MAX_N], n, a, bx, by, cx, cy, p, inv[MAX_N], max_range, dp[MAX_N];

int main()
{
    freopen("forging.in", "r", stdin);
    freopen("forging.out", "w", stdout);
    scanf("%d%d%d%d%d%d%d", &n, &a, &bx, &by, &cx, &cy, &p);
    b[0] = by + 1, max_range = max(max_range, b[0]);
    c[0] = cy + 1, max_range = max(max_range, c[0]);
    for (int i = 1; i < n; i++)
    {
        b[i] = ((long long)b[i - 1] * bx + by) % p + 1, max_range = max(max_range, b[i]);
        c[i] = ((long long)c[i - 1] * cx + cy) % p + 1, max_range = max(max_range, c[i]);
    }

    inv[1] = 1;
    for (int i = 2; i <= max_range; i++)
        inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;

    dp[0] = a;
    dp[1] = 1LL * (a + 1LL * inv[min(b[0], c[0])] * c[0] % mod * a % mod) % mod;
    for (int i = 2; i <= n; i++)
        dp[i] = (1LL * dp[i - 1] * inv[min(b[i - 2], c[i - 1])] % mod * c[i - 1] % mod + dp[i - 2]) % mod;
    printf("%d", dp[n]);
    return 0;
} // A.cpp