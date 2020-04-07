// LOJ2385.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_K = 110;

typedef pair<int, int> pii;

int n, limit, dp[MAX_N][MAX_K], max_prod[MAX_N];
deque<pii> dq[MAX_N];

struct segment
{
    int l, r;
    bool operator<(const segment &rhs) const { return l < rhs.l || (l == rhs.l && r > rhs.r); }
} segs[MAX_N];

inline char gc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return f * x;
}

int main()
{
    // freopen("2.in", "r", stdin);
    n = read(), limit = read();
    for (int i = 1; i <= n; i++)
        segs[i].l = read(), segs[i].r = read();
    sort(segs + 1, segs + 1 + n);
    int tot = 1;
    for (int i = 2; i <= n; i++)
        if (segs[i].r > segs[tot].r)
            segs[++tot] = segs[i];
    limit -= (n - tot), n = tot, limit = max(0, limit);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < min(limit + 1, i); j++)
        {
            int curt = i - j - 1;
            while (!dq[curt].empty() && segs[dq[curt].front().second].r < segs[i].l)
                // not overlap;
                max_prod[curt] = max(max_prod[curt], segs[dq[curt].front().second].r + dq[curt].front().first), dq[curt].pop_front();
            dp[i][j] = max(dp[i][j], max_prod[curt] + segs[i].r - segs[i].l);
            if (!dq[curt].empty())
                dp[i][j] = max(dp[i][j], segs[i].r + dq[curt].front().first);
            int val = dp[i][j] - segs[i].r;
            curt++;
            while (!dq[curt].empty() && dq[curt].back().first < val)
                dq[curt].pop_back();
            dq[curt].push_back(make_pair(val, i));
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < min(limit + 1, i); j++)
            if (i - j == n - limit)
                ans = max(ans, dp[i][j]);
    printf("%d\n", ans);
    return 0;
}