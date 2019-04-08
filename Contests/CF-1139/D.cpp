// D.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 200, mod = 1e9 + 7;
vector<int> facts[MAX_N], cnt[MAX_N];
ll m, dp[MAX_N], invm;
ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
int main()
{
    scanf("%lld", &m), invm = quick_pow(m, mod - 2);
    for (int i = 1; i <= m; i++)
        for (int j = i; j <= m; j += i)
            facts[j].push_back(i);
    for (int i = 1; i <= m; i++)
    {
        cnt[i].resize(facts[i].size() + 1);
        for (int j = facts[i].size() - 1; j != -1; j--)
        {
            cnt[i][j] = m / facts[i][j];
            int siz = facts[i].size();
            for (int k = j + 1; k < siz; k++)
                if (facts[i][k] % facts[i][j] == 0)
                    cnt[i][j] -= cnt[i][k];
        }
    }
    ll ans = 0;
    for (int i = 2; i <= m; i++)
    {
        int dom = m, tmp = 0;
        for (int j = 0; j < facts[i].size(); j++)
            if (facts[i][j] == i)
                dom -= cnt[i][j];
            else
                tmp = (tmp + cnt[i][j] * dp[facts[i][j]] + mod) % mod;
        dp[i] = (tmp + m + mod) % mod * quick_pow(dom, mod - 2) % mod;
    }
    for (int i = 1; i <= m; i++)
        ans = (ans + dp[i] + 1 + mod) % mod;
    printf("%lld", ans * invm % mod);
    return 0;
}