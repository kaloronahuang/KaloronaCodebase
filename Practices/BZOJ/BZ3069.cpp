// BZ3069.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100, MAX_E = 100100;

int n, m, z, ch[MAX_N][2], fa[MAX_N], mem[2][MAX_N];
bool tag[MAX_N];
char cmdlet[10];
map<pair<int, int>, int> mp;

struct edge
{
    int u, v;
    bool flag;
} edges[MAX_E];

struct queryInfo
{
    int typ, a, b;
} queries[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int find(int id, int x) { return mem[id][x] == x ? x : mem[id][x] = find(id, mem[id][x]); }

int check(int p) { return ch[find(0, fa[p])][1] == p; }

bool isRoot(int p) { return ch[find(0, fa[p])][0] != p && ch[find(0, fa[p])][1] != p; }

void pushdown(int p)
{
    if (tag[p])
    {
        swap(lson, rson);
        tag[lson] ^= 1, tag[rson] ^= 1, tag[p] = false;
    }
}

void rotate(int x)
{
    int y = find(0, fa[x]), z = find(0, fa[y]), dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
}

void update(int p)
{
    if (!isRoot(p))
        update(find(0, fa[p]));
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = find(0, fa[p]); (fat = find(0, fa[p])), !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = find(0, fa[p]))
        splay(p), rson = pre;
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, pushdown(p); }

void dfs(int u, int src)
{
    pushdown(u), mem[0][u] = src;
    for (int i = 0; i < 2; i++)
        if (ch[u][i])
            dfs(ch[u][i], src);
}

void link(int x, int y)
{
    if (find(0, x) == find(0, y))
        return;
    x = find(0, x), y = find(0, y);
    makeRoot(x), access(y), splay(y);
    if (find(1, x) != find(1, y))
        fa[x] = y, mem[1][find(1, x)] = mem[1][find(1, y)];
    else
        dfs(y, y), ch[y][0] = ch[y][1] = 0;
}

int main()
{
    scanf("%d%d%d", &n, &m, &z);
    for (int i = 1; i <= n; i++)
        mem[0][i] = mem[1][i] = i;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &edges[i].u, &edges[i].v);
        if (edges[i].u > edges[i].v)
            swap(edges[i].u, edges[i].v);
        mp[make_pair(edges[i].u, edges[i].v)] = i;
    }
    for (int i = 1; i <= z; i++)
    {
        scanf("%s%d%d", cmdlet + 1, &queries[i].a, &queries[i].b);
        if (queries[i].a > queries[i].b)
            swap(queries[i].a, queries[i].b);
        if (cmdlet[1] == 'Z')
            queries[i].typ = 1, edges[mp[make_pair(queries[i].a, queries[i].b)]].flag = true;
        else
            queries[i].typ = 2;
    }
    for (int i = 1; i <= m; i++)
        if (!edges[i].flag)
            link(edges[i].u, edges[i].v);
    stack<bool> ansBox;
    for (int i = z; i >= 1; i--)
        if (queries[i].typ == 1)
            link(queries[i].a, queries[i].b);
        else
            ansBox.push(find(0, queries[i].a) == find(0, queries[i].b));
    while (!ansBox.empty())
        puts(ansBox.top() ? "TAK" : "NIE"), ansBox.pop();
    return 0;
}