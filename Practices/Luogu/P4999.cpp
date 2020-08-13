// P4999.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 25, mod = 1e9 + 7;

int dp[MAX_N][2], cnt[MAX_N][2], bits[MAX_N], bcnt, T;

pair<int, int> dfs(int pos, bool zero, bool eq)
{
    if (pos == 0)
        return make_pair(0, 1);
    if (eq == false)
        return make_pair(dp[pos][0], cnt[pos][0]);
    int ret_val = 0, ret_cnt = 0;
    for (int i = 0; i <= bits[pos]; i++)
    {
        pair<int, int> res = dfs(pos - 1, zero && (i == 0), eq && (i == bits[pos]));
        ret_val = (0LL + ret_val + res.first + 1LL * i * res.second % mod) % mod;
        ret_cnt = (0LL + ret_cnt + res.second) % mod;
    }
    return make_pair(ret_val, ret_cnt);
}

int solve(ll x)
{
    bcnt = 0;
    while (x)
        bits[++bcnt] = x % 10, x /= 10;
    return dfs(bcnt, true, true).first;
}

int main()
{
    cnt[0][0] = 1;
    for (int i = 1, acc = 1; i <= 20; i++, acc = 10LL * acc % mod)
        for (int c = 0; c <= 9; c++)
        {
            dp[i][0] = (0LL + dp[i][0] + dp[i - 1][0] + 1LL * c * cnt[i - 1][0] % mod) % mod;
            cnt[i][0] = (0LL + cnt[i][0] + cnt[i - 1][0]) % mod;
            if (c != 0)
            {
                dp[i][1] = (0LL + dp[i][1] + dp[i - 1][0] + 1LL * c * cnt[i - 1][0] % mod) % mod;
                cnt[i][1] = (0LL + cnt[i][1] + cnt[i - 1][0]) % mod;
            }
        }
    scanf("%d", &T);
    while (T--)
    {
        ll l, r;
        scanf("%lld%lld", &l, &r), printf("%lld\n", (0LL + solve(r) + mod - solve(l - 1)) % mod);
    }
    return 0;
}