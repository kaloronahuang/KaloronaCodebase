// P2387.cpp
#include <bits/stdc++.h>
#define lson ch[p][0]
#define rson ch[p][1]

using namespace std;

const int MAX_N = 2e5 + 200;

struct edge
{
    int src, dst, ai, bi;
    bool operator<(const edge &edg) const { return ai < edg.ai || (ai == edg.ai && bi < edg.bi); }
} edges[MAX_N];

int n, m, ch[MAX_N][2], fa[MAX_N], idx[MAX_N], val[MAX_N], tag[MAX_N];

inline bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

inline int check(int p) { return ch[fa[p]][1] == p; }

inline void pushup(int p)
{
    idx[p] = p;
    if (lson && val[idx[lson]] > val[idx[p]])
        idx[p] = idx[lson];
    if (rson && val[idx[rson]] > val[idx[p]])
        idx[p] = idx[rson];
}

inline void pushdown(int p)
{
    if (tag[p])
    {
        tag[p] = 0;
        if (lson)
            tag[lson] ^= 1, swap(ch[lson][0], ch[lson][1]);
        if (rson)
            tag[rson] ^= 1, swap(ch[rson][0], ch[rson][1]);
    }
}

inline void rotate(int p)
{
    int y = fa[p], z = fa[y], dir = check(p), w = ch[p][dir ^ 1];
    fa[p] = z;
    if (!isRoot(y))
        ch[z][check(y)] = p;
    ch[y][dir] = w, fa[w] = y;
    ch[p][dir ^ 1] = y, fa[y] = p;
    pushup(y), pushup(p), pushup(z);
}

inline void jump(int p)
{
    if (!isRoot(p))
        jump(fa[p]);
    pushdown(p);
}

inline void splay(int p)
{
    jump(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(fat) == check(p) ? fat : p);
}

inline void access(int p)
{
    for (int fat = 0; p != 0; fat = p, p = fa[p])
        splay(p), ch[p][1] = fat, pushup(p);
}

inline void makeRoot(int p)
{
    access(p), splay(p);
    swap(lson, rson), tag[p] ^= 1;
}

inline int find(int p)
{
    access(p), splay(p);
    while (lson)
        p = lson;
    splay(p);
    return p;
}

inline void link(int x, int y)
{
    makeRoot(x);
    fa[x] = y;
}

inline void split(int x, int y)
{
    makeRoot(x);
    access(y), splay(y);
}

inline bool check(int x, int y)
{
    makeRoot(x);
    return find(y) == x;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &edges[i].src, &edges[i].dst, &edges[i].ai, &edges[i].bi);

    int ans = 2e9;
    sort(edges + 1, edges + 1 + m);

    for (int i = 1; i <= m; i++)
    {
        int id = i + n;
        val[id] = edges[i].bi;
        if (edges[i].src == edges[i].dst)
            continue;
        if (!check(edges[i].src, edges[i].dst))
            link(edges[i].src, id), link(id, edges[i].dst);
        else
        {
            split(edges[i].src, edges[i].dst);
            int now = idx[edges[i].dst], maxb = val[now];
            if (maxb <= edges[i].bi)
                continue;
            splay(now), fa[ch[now][0]] = fa[ch[now][1]] = 0;
            link(edges[i].src, id), link(id, edges[i].dst);
        }
        if (check(1, n))
            split(1, n), ans = min(ans, edges[i].ai + val[idx[n]]);
    }
    if (ans < 2e9)
        printf("%d", ans);
    else
        puts("-1");
    return 0;
} // P2387.cpp