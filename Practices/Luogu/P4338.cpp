// P4338.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef long long ll;

int n, q, head[MAX_N], current, ch[MAX_N][2], fa[MAX_N];
ll sum[MAX_N], val[MAX_N], vsum[MAX_N], ans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

#define lson (ch[p][0])
#define rson (ch[p][1])
#define mid ((l + r) >> 1)

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p) { sum[p] = sum[lson] + sum[rson] + val[p] + vsum[p]; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void splay(int p)
{
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
    pushup(p);
}

ll calc(int p, ll subtree, ll succ) { return rson ? (subtree - succ) * 2 : (val[p] * 2 > subtree ? (subtree - val[p]) * 2 : subtree - 1); }

void modify(int p, int delta)
{
    splay(p);
    ll subtree = sum[p] - sum[lson], succ = sum[rson];
    ans -= calc(p, subtree, succ), sum[p] += delta, subtree += delta, val[p] += delta;
    if (succ * 2 < subtree + 1)
        vsum[p] += succ, rson = 0;
    ans += calc(p, subtree, succ), pushup(p);
    int pre = p;
    p = fa[p];
    for (; p; pre = p, p = fa[p])
    {
        splay(p), subtree = sum[p] - sum[lson], succ = sum[rson];
        ans -= calc(p, subtree, succ), sum[p] += delta, vsum[p] += delta, subtree += delta;
        if (succ * 2 < subtree + 1)
            vsum[p] += succ, rson = 0, succ = 0;
        if (sum[pre] * 2 > subtree)
            vsum[p] -= sum[pre], rson = pre, succ = sum[pre];
        ans += calc(p, subtree, succ), pushup(p);
    }
}

void dfs(int u, int up)
{
    sum[u] = val[u];
    ll mx = val[u], p = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != up)
        {
            fa[edges[i].to] = u, dfs(edges[i].to, u), sum[u] += sum[edges[i].to];
            if (mx < sum[edges[i].to])
                mx = sum[edges[i].to], p = edges[i].to;
        }
    ans += min(sum[u] - 1, 2LL * (sum[u] - mx));
    if (sum[p] * 2 >= sum[u] + 1)
        ch[u][1] = p;
    vsum[u] = sum[u] - val[u] - sum[ch[u][1]];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), printf("%lld\n", ans);
    while (q--)
    {
        int u, x;
        scanf("%d%d", &u, &x), modify(u, x), printf("%lld\n", ans);
    }
    return 0;
}