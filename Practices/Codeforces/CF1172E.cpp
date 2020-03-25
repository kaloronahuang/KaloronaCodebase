// CF1172E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef long long ll;

int n, q, head[MAX_N], current, up[MAX_N], ch[MAX_N][2], fa[MAX_N], siz[MAX_N], vsiz[MAX_N], color[MAX_N];
vector<int> opts[MAX_N][2];
ll vsiz2[MAX_N], ans, delta[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

ll siz2(int p) { return 1LL * siz[p] * siz[p]; }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != up[u])
            up[edges[i].to] = u, dfs(edges[i].to);
}

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + vsiz[p] + 1; }

bool isRoot(int p) { return ch[fa[p]][1] != p && ch[fa[p]][0] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

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
            rotate(check(fat) == check(p) ? fat : p);
    pushup(p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), vsiz[p] += siz[rson] - siz[pre], vsiz2[p] += siz2(rson) - siz2(pre), rson = pre, pushup(p);
}

int find(int p)
{
    access(p), splay(p);
    while (lson)
        p = lson;
    splay(p);
    return p;
}

void link(int p)
{
    int fat = up[p];
    splay(p), ans -= vsiz2[p] + siz2(rson);
    int rt = find(fat);
    access(p), splay(rt), ans -= siz2(ch[rt][1]);
    fa[p] = fat, splay(fat), vsiz[fat] += siz[p], vsiz2[fat] += siz2(p);
    pushup(fat), access(p), splay(rt), ans += siz2(ch[rt][1]);
}

void cut(int p)
{
    int fat = up[p];
    access(p), ans += vsiz2[p];
    int rt = find(fat);
    access(p), splay(rt), ans -= siz2(ch[rt][1]);
    splay(p), lson = fa[lson] = 0, pushup(p), splay(rt), ans += siz2(ch[rt][1]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]), opts[color[i]][0].push_back(i), opts[color[i]][1].push_back(0);
    for (int i = 1; i <= n + 1; i++)
        siz[i] = 1;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1, u, v; i <= q; i++)
    {
        scanf("%d%d", &u, &v);
        opts[color[u]][0].push_back(u), opts[color[u]][1].push_back(i);
        color[u] = v;
        opts[color[u]][0].push_back(u), opts[color[u]][1].push_back(i);
    }
    ll last = 0;
    up[1] = n + 1, dfs(1);
    for (int i = 1; i <= n; i++)
        link(i);
    for (int i = 1; i <= n; i++)
    {
        if (opts[i][0].empty())
        {
            delta[0] += 1LL * n * n;
            continue;
        }
        if (opts[i][1][0])
            // dont even exist during initial time;
            delta[0] += 1LL * n * n, last = 1LL * n * n;
        else
            last = 0;
        for (int j = 0, siz = opts[i][0].size(); j < siz; j++)
        {
            int u = opts[i][0][j];
            if (tag[u])
                link(u);
            else
                cut(u);
            tag[u] ^= 1;
            if (j == opts[i][0].size() - 1 || opts[i][1][j] != opts[i][1][j + 1])
            {
                delta[opts[i][1][j]] += ans - last;
                last = ans;
            }
        }
        for (int j = opts[i][0].size() - 1; j >= 0; j--)
        {
            int u = opts[i][0][j];
            if (tag[u])
                link(u);
            else
                cut(u);
            tag[u] ^= 1;
        }
    }
    ans = 1LL * n * n * n;
    for (int i = 0; i <= q; i++)
        ans -= delta[i], printf("%lld\n", ans);
    return 0;
}