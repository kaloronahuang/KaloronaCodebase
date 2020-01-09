// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, k, nodes[MAX_N], upper;
vector<int> mp;

struct point
{
    int x, y, c;
    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y) || (x == rhs.x && y == rhs.y && c > rhs.c); }
} pts[MAX_N];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= upper; x += lowbit(x))
        nodes[x] = max(nodes[x], d);
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, nodes[x]);
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d%d", &pts[i].x, &pts[i].y, &pts[i].c);
        mp.push_back(pts[i].x), mp.push_back(pts[i].y);
    }
    pts[++k] = point{n - 1, m - 1, -1}, mp.push_back(n - 1), mp.push_back(m - 1);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    upper = mp.size();
    for (int i = 1; i <= k; i++)
        pts[i].x = ripe(pts[i].x), pts[i].y = ripe(pts[i].y);
    sort(pts + 1, pts + 1 + k);
    int ans = 0;
    for (int i = 1; i <= k; i++)
    {
        int dp = query(pts[i].y) + pts[i].c;
        if (pts[i].c == -1)
            ans = ++dp;
        update(pts[i].y, dp);
    }
    printf("%d\n", ans);
    return 0;
}