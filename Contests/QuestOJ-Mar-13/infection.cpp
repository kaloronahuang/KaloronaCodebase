// infection.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 1e9 + 7;

typedef pair<int, int> pii;

int n, dp[MAX_N], nodes[MAX_N], lower_side, preMax[MAX_N], sufMin[MAX_N];
pii pts[MAX_N], segs[MAX_N];
vector<int> vx, vv;

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= lower_side; x += lowbit(x))
        nodes[x] = (0LL + nodes[x] + mod + d) % mod;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = (0LL + ret + nodes[x]) % mod;
    return ret;
}

int ripe(vector<int> &mp, int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

void solve()
{
    for (int i = 1; i <= n; i++)
        vx.push_back(pts[i].first), vv.push_back(pts[i].second);
    sort(vx.begin(), vx.end()), sort(vv.begin(), vv.end());
    for (int i = 1; i <= n; i++)
        pts[i].first = ripe(vx, pts[i].first), pts[i].second = ripe(vv, pts[i].second);
    lower_side = vv.size();
    sort(pts + 1, pts + 1 + n);
    for (int i = 1; i <= n; i++)
        preMax[i] = max(preMax[i - 1], pts[i].second);
    sufMin[n + 1] = 0x3f3f3f3f;
    for (int i = n; i >= 1; i--)
        sufMin[i] = min(sufMin[i + 1], pts[i].second);
    for (int i = 1; i <= n; i++)
    {
        int up = preMax[i], lower = sufMin[i];
        segs[i] = make_pair(lower, up);
    }
    sort(segs + 1, segs + 1 + n, [](const pii &A, const pii &B) { return A.second < B.second || (A.second == B.second && A.first < B.first); });
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int tmp = (0LL + query(segs[i].second) - query(segs[i].first - 1) + mod + dp[segs[i].first - 1]) % mod;
        update(segs[i].second, tmp);
        dp[segs[i].second] = (0LL + dp[segs[i].second] + tmp) % mod;
    }
    printf("%d\n", dp[lower_side]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second);
    solve();
    return 0;
}