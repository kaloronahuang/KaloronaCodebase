// P2146.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_N = 1e5 + 20;
int n, head[MAX_N], current, tmpx, q, siz[MAX_N], dfn[MAX_N], low[MAX_N], son[MAX_N];
int tag[MAX_N << 1], tree[MAX_N << 2], fa[MAX_N], dep[MAX_N], tot, top[MAX_N];
char opt[20];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void update(int ql, int qr, int l, int r, int p, int c)
{
    if (ql <= l && r <= qr)
    {
        tree[p] = c * (r - l + 1), tag[p] = c;
        return;
    }
    if (tag[p] != -1)
    {
        tree[lson] = (mid - l + 1) * tag[p], tree[rson] = (r - mid) * tag[p];
        tag[lson] = tag[rson] = tag[p];
        tag[p] = -1;
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
    if (tag[p] != -1)
    {
        tree[lson] = (mid - l + 1) * tag[p], tree[rson] = (r - mid) * tag[p];
        tag[lson] = tag[rson] = tag[p];
        tag[p] = -1;
    }
    int ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}
void dfs1(int u)
{
    siz[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs1(edges[i].to);
            siz[u] += siz[edges[i].to];
            if (siz[edges[i].to] >= siz[son[u]])
                son[u] = edges[i].to;
        }
}
void dfs2(int u, int t)
{
    dfn[u] = ++tot, top[u] = t;
    if (son[u] == 0)
        return;
    dfs2(son[u], t);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
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
void build(int l, int r, int p)
{
    if (l == r)
    {
        tree[p] = 1;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    tree[p] = tree[lson] + tree[rson];
}
int main()
{
    memset(head, -1, sizeof(head)), memset(tag, -1, sizeof(tag));
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &tmpx), tmpx++, addpath(tmpx, i), addpath(i, tmpx);
    scanf("%d", &q);
    dfs1(1), dfs2(1, 1);
    while (q--)
    {
        scanf("%s%d", opt + 1, &tmpx), tmpx++;
        if (opt[1] == 'i')
        {
            int previous = tree[1];
            updateRange(1, tmpx, 1), printf("%d\n", tree[1] - previous);
        }
        else
        {
            int previous = tree[1];
            update(dfn[tmpx], dfn[tmpx] + siz[tmpx] - 1, 1, tot, 1, 0);
            printf("%d\n", previous - tree[1]);
        }
    }
    return 0;
}