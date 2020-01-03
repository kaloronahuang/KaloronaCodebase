// LOJ2187.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (5e5 + 200) * 3;

int ch[MAX_N][2], fa[MAX_N], siz[MAX_N], idx[MAX_N][3], tag[MAX_N], sum[MAX_N], val[MAX_N];
int head[MAX_N], current, n, q;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][1] != p && ch[fa[p]][0] != p; }

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + 1;
    idx[p][1] = idx[rson][1], idx[p][2] = idx[rson][2];
    if (!idx[p][1])
    {
        if (sum[p] != 1)
            idx[p][1] = p;
        else
            idx[p][1] = idx[lson][1];
    }
    if (!idx[p][2])
    {
        if (sum[p] != 2)
            idx[p][2] = p;
        else
            idx[p][2] = idx[lson][2];
    }
}

void sumup(int p, int value)
{
    sum[p] += value, val[p] = sum[p] > 1;
    swap(idx[p][1], idx[p][2]), tag[p] += value;
}

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        if (lson)
            sumup(lson, tag[p]);
        if (rson)
            sumup(rson, tag[p]);
        tag[p] = 0;
    }
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

void update(int p)
{
    if (!isRoot(p))
        update(fa[p]);
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(fat == p ? fat : p);
    pushup(p);
}

void access(int p)
{
    for (int pre = 0; p != 0; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

#undef rson
#undef lson

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), sum[u] += val[edges[i].to];
    if (u <= n)
        val[u] = sum[u] > 1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, x1, x2, x3; i <= n; i++)
    {
        scanf("%d%d%d", &x1, &x2, &x3), addpath(i, x1), addpath(i, x2), addpath(i, x3);
        fa[x1] = fa[x2] = fa[x3] = i;
    }
    for (int i = n + 1; i <= 3 * n + 1; i++)
        scanf("%d", &val[i]);
    dfs(1), scanf("%d", &q);
    int finalStat = val[1];
    while (q--)
    {
        int x, fat;
        scanf("%d", &x), fat = fa[x];
        int targetDelta = val[x] ? -1 : 1;
        access(fat), splay(fat);
        int mid = idx[fat][val[x] ? 2 : 1];
        if (mid != 0)
        {
            splay(mid), sumup(ch[mid][1], targetDelta), pushup(ch[mid][1]);
            sum[mid] += targetDelta, val[mid] = sum[mid] > 1;
            pushup(mid);
        }
        else
            // passthrough;
            finalStat ^= 1, sumup(fat, targetDelta), pushup(fat);
        val[x] ^= 1, printf("%d\n", finalStat);
    }
    return 0;
}