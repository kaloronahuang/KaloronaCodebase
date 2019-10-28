// CF1194E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e3 + 200;

struct yseg
{
    int y, x1, x2;
    bool operator<(const yseg &nd) const { return y < nd.y; }
} ysegs[MAX_N];

struct xseg
{
    int x, y1, y2;
    bool operator<(const xseg &nd) const { return y1 < nd.y1; }
} xsegs[MAX_N];

int tree[MAX_N << 1], n, xtot, ytot;

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x < (MAX_N << 1); x += lowbit(x))
        tree[x] += d;
}

int query(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree[x];
    return ret;
}

int query(int l, int r) { return query(r) - query(l - 1); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 += MAX_N + 1, y1 += MAX_N + 1, x2 += MAX_N + 1, y2 += MAX_N + 1;
        if (x1 == x2)
            xsegs[++xtot] = {x1, max(y1, y2), min(y1, y2)};
        else
            ysegs[++ytot] = {y1, max(x1, x2), min(x1, x2)};
    }
    sort(xsegs + 1, xsegs + 1 + xtot), sort(ysegs + 1, ysegs + 1 + ytot);
    long long ans = 0;
    for (int i = 1; i <= ytot; i++)
    {
        memset(tree, 0, sizeof(tree));
        queue<int> q;
        for (int j = 1; j <= xtot; j++)
            if (ysegs[i].y <= xsegs[j].y1 && ysegs[i].y >= xsegs[j].y2 && ysegs[i].x1 >= xsegs[j].x && ysegs[i].x2 <= xsegs[j].x)
                q.push(j), update(xsegs[j].x, 1);
        for (int up_side = i + 1, tmp; up_side <= ytot; up_side++)
        {
            while (!q.empty() && xsegs[q.front()].y1 < ysegs[up_side].y)
                update(xsegs[q.front()].x, -1), q.pop();
            int lft = max(ysegs[i].x2, ysegs[up_side].x2), rig = min(ysegs[i].x1, ysegs[up_side].x1);
            if (lft < rig)
                tmp = query(lft, rig), ans += (1LL * tmp * (tmp - 1)) >> 1;
        }
    }
    printf("%lld", ans);
    return 0;
}