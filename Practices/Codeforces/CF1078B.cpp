// CF1078B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7;

int n, ai[MAX_N], cnt[MAX_N], binomial[MAX_N][MAX_N], ans = 1, upper, typ;
map<pair<int, int>, int> dp, pre;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), upper = max(upper, ai[i]), typ += ((++cnt[ai[i]]) == 1);
    for (int i = 0; i <= n; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    dp[make_pair(0, 0)] = 1, pre = dp;
    for (int i = 1; i <= n; i++)
    {
        for (auto &x : pre)
        {
            pair<int, int> curt = make_pair(x.first.first + 1, x.first.second + ai[i]);
            dp[curt] = (0LL + dp[curt] + x.second) % mod;
        }
        pre = dp;
    }
    if (typ == 1 || typ == 2)
        printf("%d\n", n);
    else
    {
        for (int w = 1; w <= upper; w++)
            for (int i = 2; i <= cnt[w]; i++)
            {
                int val = dp[make_pair(i, i * w)];
                if (dp[make_pair(i, i * w)] == binomial[cnt[w]][i])
                    ans = max(ans, i);
            }
        printf("%d\n", ans);
    }
    return 0;
}