// P3750.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e5 + 3;

int n, k, ai[MAX_N], inv[MAX_N], dp[MAX_N];
vector<int> sigma[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            sigma[j].push_back(i);
    inv[0] = inv[1] = 1;
    for (int i = 2; i < mod; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    int threshold = 0;
    for (int i = n; i >= 1; i--)
        if (ai[i])
        {
            threshold++;
            for (int v : sigma[i])
                ai[v] ^= 1;
        }
    dp[n] = 1;
    for (int i = n - 1; i > k; i--)
        dp[i] = (0LL + n + 1LL * (n - i) * dp[i + 1] % mod) % mod * inv[i] % mod;
    for (int i = k; i >= 1; i--)
        dp[i] = 1;
    int ans = 0;
    for (int i = 1; i <= threshold; i++)
        ans = (0LL + ans + dp[i]) % mod;
    for (int i = 1; i <= n; i++)
        ans = 1LL * ans * i % mod;
    printf("%d\n", ans);
    return 0;
}