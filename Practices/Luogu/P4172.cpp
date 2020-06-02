// P4172.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int n, m, q, ch[MAX_N][2], fa[MAX_N], val[MAX_N], prod[MAX_N], mp[MAX_N], ansBox[MAX_N];
bool revTag[MAX_N];
map<pii, int> ids;

struct edge
{
    int src, dst, weight, id;
    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
} edges[MAX_N];

struct queryInfo
{
    int k, u, v;
} queries[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p)
{
    prod[p] = val[p] = p > n ? p : 0;
    if (lson)
        prod[p] = max(prod[p], prod[lson]);
    if (rson)
        prod[p] = max(prod[p], prod[rson]);
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

void pushdown(int p)
{
    if (revTag[p])
    {
        swap(lson, rson);
        revTag[lson] ^= 1, revTag[rson] ^= 1;
        revTag[p] = 0;
    }
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
            rotate(check(p) == check(fat) ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    splay(p);
    return p;
}

void makeRoot(int p) { access(p), splay(p), revTag[p] ^= 1, pushdown(p); }

void link(int x, int y)
{
    makeRoot(x), fa[x] = y;
}

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

void cut(int x, int y) { makeRoot(x), access(y), splay(y), ch[y][0] = fa[x] = 0; }

int main()
{

    freopen("P4172_2.in", "r", stdin);
    freopen("P4172_2.out", "w", stdout);

    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &edges[i].src, &edges[i].dst, &edges[i].weight);
        if (edges[i].src > edges[i].dst)
            swap(edges[i].src, edges[i].dst);
    }
    sort(edges + 1, edges + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        mp[i] = edges[i].weight, edges[i].weight = i;
        ids[make_pair(edges[i].src, edges[i].dst)] = i;
    }
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d", &queries[i].k, &queries[i].u, &queries[i].v);
        if (queries[i].u > queries[i].v)
            swap(queries[i].u, queries[i].v);
        if (queries[i].k == 2)
            edges[ids[make_pair(queries[i].u, queries[i].v)]].id = i;
    }
    for (int i = 1; i <= m; i++)
        if (edges[i].id == 0 && find(edges[i].src) != find(edges[i].dst))
            link(edges[i].src, edges[i].weight + n), link(edges[i].dst, edges[i].weight + n);
    int qtot = 0;
    for (int i = q; i >= 1; i--)
        if (queries[i].k == 1)
        {
            split(queries[i].u, queries[i].v);
            ansBox[++qtot] = mp[edges[prod[queries[i].v] - n].weight];
        }
        else
        {
            int id = ids[make_pair(queries[i].u, queries[i].v)];
            if (find(edges[id].src) != find(edges[id].dst))
            {
                link(edges[id].src, edges[id].weight + n);
                link(edges[id].dst, edges[id].weight + n);
            }
            else
            {
                split(edges[id].src, edges[id].dst);
                int max_val = prod[edges[id].dst];
                /*
                if (max_val == 100 && max_val - n > edges[id].weight)
                    puts("FUCK");
                */
                if (edges[max_val - n].weight > edges[id].weight)
                {
                    cut(edges[max_val - n].src, edges[max_val - n].weight + n);
                    cut(edges[max_val - n].dst, edges[max_val - n].weight + n);
                    link(edges[id].src, edges[id].weight + n);
                    link(edges[id].dst, edges[id].weight + n);
                }
            }
        }

    for (int i = qtot; i >= 1; i--)
        printf("%d\n", ansBox[i]);
    return 0;
}