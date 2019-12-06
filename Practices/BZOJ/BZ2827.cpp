// BZ2827.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 700100, INF = 0x7fffffff;

int n, T, forces[MAX_N], xi[MAX_N], yi[MAX_N], idx[MAX_N], ncnt, fans[MAX_N], nans[MAX_N], roots[MAX_N];
int ccnt[MAX_N];

struct point
{
    int x, y;
    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
    bool operator==(const point &rhs) const { return x == rhs.x && y == rhs.y; }
} pts[MAX_N];

struct node
{
    int ch[2], siz, force, aff, fa, ftag, ntag;
} nodes[MAX_N];

#define lson nodes[p].ch[0]
#define rson nodes[p].ch[1]

void pushdown(int p)
{
    fans[p] = max(fans[p], nodes[p].ftag);
    nans[p] = max(nans[p], nodes[p].ntag);
    nodes[lson].ftag = max(nodes[lson].ftag, nodes[p].ftag);
    nodes[rson].ftag = max(nodes[rson].ftag, nodes[p].ftag);
    nodes[lson].ntag = max(nodes[lson].ntag, nodes[p].ntag);
    nodes[rson].ntag = max(nodes[rson].ntag, nodes[p].ntag);
    nodes[p].ftag = nodes[p].ntag = 0;
}

int check(int p) { return nodes[nodes[p].fa].ch[1] == p; }

void rotate(int x)
{
    int y = nodes[x].fa, z = nodes[y].fa, dir = check(x), w = nodes[x].ch[dir ^ 1];
    pushdown(y), pushdown(x);
    nodes[x].fa = z;
    if (z != 0)
        nodes[z].ch[nodes[z].ch[1] == y] = x;
    nodes[w].fa = y, nodes[y].ch[dir] = w;
    nodes[y].fa = x, nodes[x].ch[dir ^ 1] = y;
}

void splay(int rt, int p, int goal = 0)
{
    for (int fat = nodes[p].fa; (fat = nodes[p].fa) != goal; rotate(p))
        if (nodes[fat].fa != goal)
            rotate(check(p) == check(fat) ? fat : p);
    if (goal == 0)
        roots[rt] = p;
}

int previous(int rt, int p)
{
    splay(rt, p), p = lson;
    while (rson)
        p = rson;
    return p;
}

void insert(int rt, int p)
{
    nodes[p].aff = rt;
    int curt = roots[rt];
    pushdown(curt);
    while (nodes[curt].ch[nodes[p].force > nodes[curt].force])
        pushdown(curt = nodes[curt].ch[nodes[p].force > nodes[curt].force]);
    nodes[p].fa = curt, nodes[curt].ch[nodes[p].force > nodes[curt].force] = p;
    ccnt[rt]++, splay(rt, p);
    int rbound = previous(rt, n + (rt << 1)), rrbound = previous(rt, rbound);
    if (rbound <= n)
    {
        pushdown(rbound);
        nodes[rbound].ntag = ccnt[rt] - 1;
        fans[rbound] = max(fans[rbound], nodes[rrbound].force);
        int ls = nodes[rbound].ch[0], rs = nodes[rbound].ch[1];
        nodes[ls].ftag = max(nodes[ls].ftag, nodes[rbound].force);
        nodes[rs].ftag = max(nodes[rs].ftag, nodes[rbound].force);
    }
}

void remove(int rt, int p)
{
    int pre = previous(rt, p);
    splay(rt, pre), splay(rt, p, pre);
    pushdown(pre), pushdown(p);
    nodes[rson].fa = pre, nodes[pre].ch[1] = rson;
    ccnt[rt]--, lson = rson = nodes[p].fa = nodes[p].aff = 0;
}

int main()
{
    // input part;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &forces[i], &xi[i], &yi[i]);
        pts[++ncnt] = {xi[i], yi[i]}, nodes[i].force = forces[i];
    }
    scanf("%d", &T);
    for (int i = n + 1; i <= n + T; i++)
    {
        scanf("%d%d%d", &idx[i], &xi[i], &yi[i]);
        pts[++ncnt] = {xi[i], yi[i]};
    }
    sort(pts + 1, pts + 1 + ncnt), ncnt = unique(pts + 1, pts + 1 + ncnt) - pts - 1;
    // init for splay;
    // the inf pts;
    for (int i = 1; i <= ncnt; i++)
    {
        int pos = n + (i << 1), neg = pos - 1;
        roots[i] = neg;
        nodes[pos].force = INF, nodes[neg].force = -INF;
        nodes[neg].ch[1] = pos, nodes[pos].fa = neg;
    }
    for (int i = 1; i <= n; i++)
    {
        int posId = lower_bound(pts + 1, pts + 1 + ncnt, point{xi[i], yi[i]}) - pts;
        insert(posId, i);
    }
    for (int i = n + 1; i <= n + T; i++)
    {
        remove(nodes[idx[i]].aff, idx[i]);
        int posId = lower_bound(pts + 1, pts + 1 + ncnt, point{xi[i], yi[i]}) - pts;
        insert(posId, idx[i]);
        xi[idx[i]] = xi[i], yi[idx[i]] = yi[i];
    }
    for (int i = 1; i <= n; i++)
        remove(nodes[i].aff, i);
    for (int i = 1; i <= n; i++)
        printf("%lld ", 1LL * fans[i] * nans[i]);
    return 0;
}