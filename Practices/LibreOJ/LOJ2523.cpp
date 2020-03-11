// LOJ2523.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, q, P, vi[MAX_N], factors[MAX_N], ftot, pow2[MAX_N], dp[2020][2020], cnt[MAX_N], ans[MAX_N];
map<int, int> idsys;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d%d%d", &n, &q, &P);
    for (int i = 1; i <= n; i++)
        scanf("%d", &vi[i]), vi[i] = gcd(vi[i], P);
    sort(vi + 1, vi + 1 + n);
    int tot = 0;
    for (int i = 1; i <= n; i++)
        if (vi[i] == vi[tot])
            cnt[tot]++;
        else
            vi[++tot] = vi[i], cnt[tot]++;
    n = tot;
    for (int i = 1; 1LL * i * i <= P; i++)
        if (P % i == 0)
        {
            factors[++ftot] = i;
            if (1LL * i * i != P)
                factors[++ftot] = P / i;
        }
    sort(factors + 1, factors + 1 + ftot);
    for (int i = 1; i <= ftot; i++)
        idsys[factors[i]] = i;
    for (int i = pow2[0] = 1; i < MAX_N; i++)
        pow2[i] = 1LL * pow2[i - 1] * 2 % mod;
    dp[0][ftot] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= ftot; j++)
        {
            int d = idsys[gcd(factors[j], vi[i])];
            dp[i][j] = (0LL + dp[i][j] + dp[i - 1][j]) % mod;
            dp[i][d] = (0LL + dp[i][d] + 1LL * dp[i - 1][j] * (pow2[cnt[i]] + mod - 1) % mod) % mod;
        }
    for (int i = 1; i <= ftot; i++)
        for (int j = 1; j <= i; j++)
            if (factors[i] % factors[j] == 0)
                ans[i] = (0LL + ans[i] + dp[n][j]) % mod;
    while (q--)
    {
        int w;
        scanf("%d", &w);
        printf("%d\n", ans[idsys[gcd(P, w)]]);
    }
    return 0;
}