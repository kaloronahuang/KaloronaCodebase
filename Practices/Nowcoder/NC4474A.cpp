// NC4474A.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353, MAX_N = 4e5 + 200;

int n, m, k, dp[2200][2200], fac[MAX_N], fac_inv[MAX_N];
bool mp[2200][2200];
pair<int, int> obs[20];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void subtask1()
{
    for (int i = 1, x, y; i <= k; i++)
        scanf("%d%d", &x, &y), mp[x][y] = true;
    dp[n + 1][0] = 1;
    for (int i = n + 1; i >= 1; i--)
        for (int j = 1; j <= m + 1; j++)
            if (mp[i][j] == false)
                dp[i][j] = (0LL + dp[i + 1][j] + dp[i][j - 1]) % mod;
    printf("%d\n", dp[1][m + 1]);
}

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    if (max(n, m) <= 1000)
        subtask1();
    else
    {
        for (int i = fac[0] = 1; i < MAX_N; i++)
            fac[i] = 1LL * fac[i - 1] * i % mod;
        fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
        for (int i = MAX_N - 1 - 1; i >= 0; i--)
            fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
        for (int i = 0; i < k; i++)
            scanf("%d%d", &obs[i].first, &obs[i].second);
        sort(obs, obs + k, [](const pair<int, int> &a, const pair<int, int> &b) { return a.second < b.second; });
        obs[k] = make_pair(1, m + 1);
        int ans = 0;
        for (int stat = 0; stat < (1 << k); stat++)
        {
            int pans = 1;
            pair<int, int> last = make_pair(n + 1, 1);
            for (int j = 0; j <= k; j++)
                if (j == k || (stat & (1 << j)))
                {
                    pair<int, int> curt = obs[j];
                    if (curt.first <= last.first && curt.second >= last.second)
                        pans = 1LL * pans * binomial(last.first - curt.first + curt.second - last.second, curt.second - last.second) % mod;
                    else
                    {
                        pans = 0;
                        break;
                    }
                    last = curt;
                }
            if (__builtin_popcount(stat) & 1)
                ans = (0LL + ans + mod - pans) % mod;
            else
                ans = (0LL + ans + pans) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}