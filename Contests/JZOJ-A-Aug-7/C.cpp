// C.cpp
#include <bits/stdc++.h>
#define ll long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, current, head[MAX_N], dfn[MAX_N], low[MAX_N], tot, rectot;
ll tree[MAX_N << 2], tag[MAX_N << 2];

struct edge
{
    int to, nxt;
} edges[MAX_N];

struct line_node
{
    int x, y1, y2, aff;
    bool operator<(const line_node &ln) const { return x < ln.x; }
} nodes[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    dfn[u] = ++tot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    low[u] = tot;
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql == l && r == qr)
    {
        tag[p] += val;
        if (tag[p])
            tree[p] = (r - l + 1);
        else if (l == r)
            tree[p] = 0;
        else
            tree[p] = tree[lson] + tree[rson];
        return;
    }
    if (qr <= mid)
        update(ql, qr, l, mid, lson, val);
    else if (ql > mid)
        update(ql, qr, mid + 1, r, rson, val);
    else
        update(ql, mid, l, mid, lson, val), update(mid + 1, qr, mid + 1, r, rson, val);
    if (tag[p])
        tree[p] = r - l + 1;
    else
        tree[p] = tree[lson] + tree[rson];
}

void create_rectangle(int x1, int x2, int y1, int y2)
{
    if (x1 > x2)
        swap(x1, x2);
    if (y1 > y2)
        swap(y1, y2);
    nodes[++rectot] = line_node{x1, y1, y2, 1};
    nodes[++rectot] = line_node{x2 + 1, y1, y2, -1};
}

ll process_pair()
{
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (dfn[x] > dfn[y])
            swap(x, y);
        if (dfn[x] < dfn[y] && dfn[y] <= low[x])
        {
            if (dfn[x] != 1)
                create_rectangle(1, dfn[x], dfn[y], low[y]);
            if (low[x] != n)
                create_rectangle(dfn[y], low[y], low[x] + 1, n);
        }
        else
            create_rectangle(dfn[x], low[x], dfn[y], low[y]);
    }
    sort(nodes + 1, nodes + 1 + rectot);
    long long answer = 0;
    for (int i = 1, cur = 1; i <= n; i++)
    {
        while (cur <= rectot && nodes[cur].x <= i)
            update(nodes[cur].y1, nodes[cur].y2, 1, n, 1, nodes[cur].aff), cur++;
        answer += tree[1];
    }
    return answer;
}

int main()
{
    /*
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
    */
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= n - 1; i++)
        scanf("%d%d", &x, &y), addpath(x, y), addpath(y, x);
    dfs(1, 0);
    printf("%lld", ((n * (n - 1)) >> 1) - process_pair());
    return 0;
}