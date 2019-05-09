// CF1156F.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5050, mod = 998244353;

int n, arr[MAX_N], cnt[MAX_N], dp[MAX_N][MAX_N], sum[MAX_N][MAX_N], inv[MAX_N];

int quick_pow(int bas, int tim)
{
    bas %= mod;
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        inv[i] = quick_pow(i, mod - 2);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), cnt[arr[i]]++;
    cnt[0] = 1;
    for (int i = n; i >= 0; i--)
    {
        for (int j = n; j >= 0; j--)
        {
            if (cnt[i] == 0 || j == n)
            {
                sum[i][j] = (sum[i + 1][j] + sum[i][j]) % mod;
                continue;
            }
            dp[i][j] = (cnt[i] - 1) * 1LL * inv[n - j] % mod;
            dp[i][j] = (dp[i][j] + sum[i + 1][j + 1] * 1LL * inv[n - j] % mod) % mod;
            sum[i][j] = (sum[i][j] + sum[i + 1][j]) % mod;
            sum[i][j] = (sum[i][j] + dp[i][j] * 1LL * cnt[i] % mod) % mod;
        }
    }
    printf("%d", dp[0][0]);
    return 0;
}