// UOJ275.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7, inv2 = 500000004;

int T, k, dp[MAX_N][2][2], digit_n[MAX_N], digit_m[MAX_N];
ll n, m;

int main()
{
    scanf("%d%d", &T, &k);
    while (T--)
    {
        scanf("%lld%lld", &n, &m);
        memset(dp, 0, sizeof(dp));
        ll a = n, b = m;
        memset(digit_n, 0, sizeof(digit_n));
        memset(digit_m, 0, sizeof(digit_m));
        while (a)
            digit_n[++digit_n[0]] = a % k, a /= k;
        while (b)
            digit_m[++digit_m[0]] = b % k, b /= k;
        for (int i = 0; i < k; i++)
            for (int j = 0; j <= i; j++)
                dp[1][i > digit_n[1]][j > digit_m[1]]++;
        for (int i = 2; i <= max(digit_n[0], digit_m[0]); i++)
            for (int da = 0; da <= k - 1; da++)
                for (int db = 0; db <= da; db++)
                {
                    // basic preperation;
                    if (da < digit_n[i] && db < digit_m[i])
                    {
                        dp[i][0][0] = (1LL * dp[i][0][0] + dp[i - 1][0][0] + dp[i - 1][0][1]) % mod;
                        dp[i][0][0] = (1LL * dp[i][0][0] + dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da < digit_n[i] && db > digit_m[i])
                    {
                        dp[i][0][1] = (1LL * dp[i][0][1] + dp[i - 1][0][0] + dp[i - 1][0][1]) % mod;
                        dp[i][0][1] = (1LL * dp[i][0][1] + dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da > digit_n[i] && db < digit_m[i])
                    {
                        dp[i][1][0] = (1LL * dp[i][1][0] + dp[i - 1][0][0] + dp[i - 1][0][1]) % mod;
                        dp[i][1][0] = (1LL * dp[i][1][0] + dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da > digit_n[i] && db > digit_m[i])
                    {
                        dp[i][1][1] = (1LL * dp[i][1][1] + dp[i - 1][0][0] + dp[i - 1][0][1]) % mod;
                        dp[i][1][1] = (1LL * dp[i][1][1] + dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da == digit_n[i] && db == digit_m[i])
                    {
                        dp[i][0][0] = (1LL * dp[i][0][0] + dp[i - 1][0][0]) % mod;
                        dp[i][1][0] = (1LL * dp[i][1][0] + dp[i - 1][1][0]) % mod;
                        dp[i][0][1] = (1LL * dp[i][0][1] + dp[i - 1][0][1]) % mod;
                        dp[i][1][1] = (1LL * dp[i][1][1] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da < digit_n[i] && db == digit_m[i])
                    {
                        dp[i][0][0] = (1LL * dp[i][0][0] + dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
                        dp[i][0][1] = (1LL * dp[i][0][1] + dp[i - 1][0][1] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da == digit_n[i] && db < digit_m[i])
                    {
                        dp[i][0][0] = (1LL * dp[i][0][0] + dp[i - 1][0][0] + dp[i - 1][0][1]) % mod;
                        dp[i][1][0] = (1LL * dp[i][1][0] + dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
                    }
                    else if (da > digit_n[i] && db == digit_m[i])
                    {
                        dp[i][1][0] = (1LL * dp[i][1][0] + dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
                        dp[i][1][1] = (1LL * dp[i][1][1] + dp[i - 1][0][1] + dp[i - 1][1][1]) % mod;
                    }
                    else
                    {
                        dp[i][0][1] = (1LL * dp[i][0][1] + dp[i - 1][0][0] + dp[i - 1][0][1]) % mod;
                        dp[i][1][1] = (1LL * dp[i][1][1] + dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
                    }
                }
        int ans = 1LL * (n + 1LL) % mod * ((n + 2LL) % mod) % mod * inv2 % mod;
        if (n > m)
            ans = (1LL * ans - 1LL * ((n - m + 0LL) % mod) * ((n - m + 1LL) % mod) % mod * inv2 % mod + mod) % mod;
        ans = (1LL * ans - dp[max(digit_n[0], digit_m[0])][0][0] + mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}