// BZ3928.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 660;

int T, n, dp[MAX_N][MAX_N];
vector<int> mp;

struct segment
{
    int l, r, val;
    bool operator<(const segment &rhs) const { return val > rhs.val; }
} segs[MAX_N];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int solve(int l, int r)
{
    if (l > r)
        return 0;
    if (dp[l][r] != -1)
        return dp[l][r];
    int pos = 0;
    for (int i = 1; i <= n; i++)
        if (l <= segs[i].l && segs[i].r <= r)
        {
            pos = i;
            break;
        }
    if (pos == 0)
        return dp[l][r] = 0;
    dp[l][r] = 0x3f3f3f3f;
    for (int i = segs[pos].l; i <= segs[pos].r; i++)
        dp[l][r] = min(dp[l][r], solve(l, i - 1) + solve(i + 1, r) + segs[pos].val);
    return dp[l][r];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        mp.clear();
        memset(dp, -1, sizeof(dp));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &segs[i].l, &segs[i].r, &segs[i].val);
            mp.push_back(segs[i].l), mp.push_back(segs[i].r);
        }
        sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
        for (int i = 1; i <= n; i++)
            segs[i].l = ripe(segs[i].l), segs[i].r = ripe(segs[i].r);
        sort(segs + 1, segs + 1 + n), printf("%d\n", solve(1, mp.size()));
    }
    return 0;
}