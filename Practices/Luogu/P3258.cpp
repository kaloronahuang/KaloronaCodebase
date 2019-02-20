// P3258.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_N = 300020;
int head[MAX_N], current, dfn[MAX_N], antidfn[MAX_N], low[MAX_N], son[MAX_N];
int siz[MAX_N], top[MAX_N], fa[MAX_N], dep[MAX_N], tot, tmp, tmpx, tmpy;
int tree[MAX_N << 2], lazy[MAX_N << 2], arr[MAX_N], step;
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs2(int u, int org)
{
    top[u] = org, dfn[u] = ++tot, antidfn[tot] = u, low[u] = tot;
    if (son[u] == -1)
        return;
    dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
    low[u] = tot;
}
void dfs1(int u)
{
    siz[u] = 1, son[u] = -1;
    int key = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == fa[u])
            continue;
        dep[edges[i].to] = dep[u] + 1, fa[edges[i].to] = u;
        dfs1(edges[i].to);
        siz[u] += siz[edges[i].to];
        if (siz[edges[i].to] > key)
            key = siz[edges[i].to], son[u] = edges[i].to;
    }
}
void update(int ql, int qr, int l, int r, int p, int c)
{
    if (ql <= l && r <= qr)
    {
        tree[p] += c * (r - l + 1), lazy[p] += c;
        return;
    }
    if (lazy[p])
    {
        tree[lson] += (mid - l + 1) * lazy[p], tree[rson] += (r - mid) * lazy[p];
        lazy[lson] += lazy[p], lazy[rson] += lazy[p];
        lazy[p] = 0;
    }
    if (ql <= mid)
        update(ql, qr, l, mid, lson, c);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, c);
    tree[p] = tree[lson] + tree[rson];
}
int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    if (lazy[p])
    {
        tree[lson] += (mid - l + 1) * lazy[p], tree[rson] += (r - mid) * lazy[p];
        lazy[lson] += lazy[p], lazy[rson] += lazy[p];
        lazy[p] = 0;
    }
    int ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}
void updateRange(int x, int y, int c)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(dfn[top[x]], dfn[x], 1, tot, 1, c);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(dfn[x], dfn[y], 1, tot, 1, c);
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &step);
    for (int i = 1; i <= step; i++)
        scanf("%d", &arr[i]);
    for (int i = 1; i < step; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dep[arr[1]] = 1;
    dfs1(arr[1]);
    dfs2(arr[1], arr[1]);
    int nowpt = 0;
    for (int i = 2; i <= step; i++)
    {
        if (nowpt != 0)
            update(dfn[nowpt], dfn[nowpt], 1, tot, 1, -1);
        updateRange(arr[i], arr[i - 1], 1), nowpt = arr[i];
    }
    for (int i = 1; i <= step; i++)
        if (i != arr[step])
            printf("%d\n", query(dfn[i], dfn[i], 1, tot, 1));
        else
            printf("%d\n", query(dfn[i], dfn[i], 1, tot, 1) - 1);
    return 0;
}