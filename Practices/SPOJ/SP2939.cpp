// SP2939.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000, INF = 0x3f3f3f3f;

int head[MAX_N], n, q, current, ch[MAX_N][2], fa[MAX_N], siz[MAX_N], lmn[MAX_N], rmn[MAX_N];
bool color[MAX_N];
multiset<int> ms[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int topElement(int x) { return ms[x].empty() ? INF : *ms[x].begin(); }

int isRoot(int p) { return ch[fa[p]][1] != p && ch[fa[p]][0] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + 1;
    lmn[p] = min(lmn[lson], siz[lson] + min(color[p] ? 0 : INF, min(topElement(p), lmn[rson] + 1)));
    rmn[p] = min(rmn[rson], siz[rson] + min(color[p] ? 0 : INF, min(topElement(p), rmn[lson] + 1)));
}

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
            rotate(fat == p ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p != 0; pre = p, p = fa[p])
    {
        splay(p), ms[p].insert(lmn[rson] + 1), rson = pre;
        multiset<int>::iterator it = ms[p].find(lmn[rson] + 1);
        if (it != ms[p].end())
            ms[p].erase(it);
        pushup(p);
    }
}

#undef rson
#undef lson

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            ms[u].insert(INF + 1), fa[edges[i].to] = u, pushup(u), dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), lmn[0] = rmn[0] = INF;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    scanf("%d", &q), dfs(1, 0);
    while (q--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            access(x), splay(x), printf("%d\n", rmn[x] > n ? -1 : rmn[x]);
        else
            access(x), splay(x), color[x] ^= 1, pushup(x);
    }
    return 0;
}