// P4234.cpp
#include <bits/stdc++.h>
#define lson (ch[p][0])
#define rson (ch[p][1])

using namespace std;

const int MAX_N = 50000 + 5, MAX_E = 200005;
const long long INF = (1LL << 62);

struct edge
{
    int src, dst, weight, id;
    bool operator<(const edge &target) const { return weight < target.weight; }
} edges[MAX_E << 1];

int n, m, fa[MAX_E << 1], idx[MAX_E << 1], ch[MAX_E << 1][2];
bool tag[MAX_E << 1], book[MAX_E << 1];

int check(int x) { return ch[fa[x]][1] == x; }

bool isRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

inline void update(int p)
{
    idx[p] = p;
    if (idx[lson] > n && (idx[p] <= n || idx[p] > idx[lson]))
        idx[p] = idx[lson];
    if (idx[rson] > n && (idx[p] <= n || idx[p] > idx[rson]))
        idx[p] = idx[rson];
}

inline void pushdown(int p)
{
    if (tag[p])
    {
        if (lson)
            tag[lson] ^= 1, swap(ch[lson][0], ch[lson][1]);
        if (rson)
            tag[rson] ^= 1, swap(ch[rson][0], ch[rson][1]);
        tag[p] = 0;
    }
}

inline void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    ch[y][dir] = w, fa[w] = y;
    ch[x][dir ^ 1] = y, fa[y] = x;
    update(y), update(x), update(z);
}

inline void jump(int x)
{
    if (!isRoot(x))
        jump(fa[x]);
    pushdown(x);
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
        splay(p), ch[p][1] = fat, update(p);
}

inline void makeRoot(int p)
{
    access(p), splay(p);
    swap(lson, rson), tag[p] ^= 1;
}

inline int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    splay(p);
    return p;
}

inline void link(int x, int y)
{
    makeRoot(x);
    fa[x] = y;
}

inline void split(int x, int y) { makeRoot(x), access(y), splay(y); }

inline bool judge(int x, int y)
{
    makeRoot(x);
    return (find(y) == x);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), edges[i].src = x, edges[i].dst = y, edges[i].weight = w;
    sort(edges + 1, edges + 1 + m);

    for (int i = 1; i <= m; i++)
        edges[i].id = n + i;

    long long answer = INF, lbound = 1, block_num = 0;
    for (int i = 1; i <= m; i++)
    {
        if (edges[i].src == edges[i].dst)
        {
            book[i] = true;
            continue;
        }

        if (!judge(edges[i].src, edges[i].dst))
            link(edges[i].src, edges[i].id), link(edges[i].id, edges[i].dst), block_num++;
        else
        {
            split(edges[i].src, edges[i].dst);
            int now = idx[edges[i].dst];
            book[now - n] = true, splay(now);
            fa[ch[now][0]] = fa[ch[now][1]] = 0;
            link(edges[i].src, edges[i].id), link(edges[i].id, edges[i].dst);
        }
        while (book[lbound] && lbound <= i)
            lbound++;
        if (block_num >= n - 1)
            answer = min(answer, 1LL * edges[i].weight - 1LL * edges[lbound].weight);
    }
    printf("%lld", answer);
    return 0;
}