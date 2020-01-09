// FOJ3742.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, ai[MAX_N], nodes[MAX_N], dp[MAX_N], pre[MAX_N], pre_dp[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (int siz = mp.size(); x <= siz; x += lowbit(x))
        nodes[x] = (1LL * nodes[x] + d) % mod;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = (1LL * ret + nodes[x]) % mod;
    return ret;
}

void fileIO()
{
    freopen("subsequence.in", "r", stdin);
    freopen("subsequence.out", "w", stdout);
}

int main()
{
    fileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mp.push_back(ai[i]);
    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        ai[i] = ripe(ai[i]);
    update(ai[1], 1), pre[ai[1]] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = (0LL + query(ai[i] - 1) + mod - pre_dp[ai[i]]) % mod;
        update(ai[i], (dp[i] + (pre[ai[i]] == 0)) % mod);
        pre_dp[ai[i]] = (0LL + pre_dp[ai[i]] + dp[i]) % mod, pre[ai[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (1LL * ans + dp[i]) % mod;
    printf("%d\n", ans);
    return 0;
}