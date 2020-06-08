// P4495.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, m, P, vi[MAX_N], factors[MAX_N], ftot, dp[2020][2020], ans[MAX_N], bin[MAX_N], cnt[MAX_N];
map<int, int> idx;

int main()
{
    scanf("%d%d%d", &n, &m, &P);
    for (int i = 1; i <= n; i++)
        scanf("%d", &vi[i]), vi[i] = __gcd(vi[i], P);
    sort(vi + 1, vi + 1 + n);
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {
        if (vi[i] != vi[i - 1])
            vi[++tot] = vi[i];
        cnt[tot]++;
    }
    n = tot;
    for (int i = bin[0] = 1; i < MAX_N; i++)
        bin[i] = 2LL * bin[i - 1] % mod;
    int acc = P;
    for (int i = 1; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            factors[++ftot] = i;
            if (acc / i != i)
                factors[++ftot] = acc / i;
        }
    sort(factors + 1, factors + 1 + ftot);
    for (int i = 1; i <= ftot; i++)
        idx[factors[i]] = i;
    dp[0][ftot] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= ftot; j++)
        {
            int d = idx[__gcd(factors[j], vi[i])];
            dp[i][j] = (0LL + dp[i][j] + dp[i - 1][j]) % mod;
            dp[i][d] = (0LL + dp[i][d] + 1LL * dp[i - 1][j] * (0LL + bin[cnt[i]] + mod - 1) % mod) % mod;
        }
    for (int i = 1; i <= ftot; i++)
        for (int j = 1; j <= i; j++)
            if (factors[i] % factors[j] == 0)
                ans[i] = (0LL + ans[i] + dp[n][j]) % mod;
    while (m--)
    {
        int w;
        scanf("%d", &w);
        printf("%d\n", ans[idx[__gcd(w, P)]]);
    }
    return 0;
}