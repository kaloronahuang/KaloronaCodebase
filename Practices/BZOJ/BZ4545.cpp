// BZ4545.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int tid, n, q, head[MAX_N], current, pos[MAX_N];
ll strtot;
char cmdlet[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

namespace LCT
{

    int ch[MAX_N][2], fa[MAX_N];
    ll tag[MAX_N], val[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

    // LCT funcs;

    int check(int x) { return ch[fa[x]][1] == x; }

    bool isRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    void pushdown(int p)
    {
        if (tag[p])
        {
            if (lson)
                val[lson] += tag[p], tag[lson] += tag[p];
            if (rson)
                val[rson] += tag[p], tag[rson] += tag[p];
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
                rotate(check(fat) == check(p) ? fat : p);
    }

    void access(int p)
    {
        for (int pre = 0; p; pre = p, p = fa[p])
            splay(p), rson = pre;
    }

    void link(int x, int up) { access(up), splay(up), fa[x] = up, val[up] += val[x], tag[up] += val[x]; }

    void cut(int p) { access(p), splay(p), val[lson] -= val[p], tag[lson] -= val[p], lson = fa[lson] = 0; }

} // namespace LCT

namespace SAM
{

    struct node
    {
        int ch[26], link, dep;
    } nodes[MAX_N << 1];

    int ptot = 1;

    int insert(int c, int pre)
    {
        int p = ++ptot;
        nodes[p].dep = nodes[pre].dep + 1, LCT::val[p] = 1;
        while (pre && nodes[pre].ch[c] == 0)
            nodes[pre].ch[c] = p, pre = nodes[pre].link;
        if (pre == 0)
            nodes[p].link = 1, strtot += nodes[p].dep - nodes[nodes[p].link].dep, LCT::link(p, nodes[p].link);
        else
        {
            int q = nodes[pre].ch[c];
            if (nodes[q].dep == nodes[pre].dep + 1)
                nodes[p].link = q, LCT::link(p, q), strtot += nodes[p].dep - nodes[nodes[p].link].dep;
            else
            {
                int clone = ++ptot;
                nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
                strtot += nodes[clone].dep - nodes[nodes[clone].link].dep;
                strtot -= nodes[q].dep - nodes[nodes[q].link].dep;
                LCT::cut(q);
                nodes[p].link = clone, nodes[q].link = clone;
                strtot += nodes[p].dep - nodes[nodes[p].link].dep;
                strtot += nodes[q].dep - nodes[nodes[q].link].dep;
                LCT::link(p, nodes[p].link), LCT::link(q, nodes[q].link), LCT::link(clone, nodes[clone].link);
                while (pre && nodes[pre].ch[c] == q)
                    nodes[pre].ch[c] = clone, pre = nodes[pre].link;
            }
        }
        return p;
    }

} // namespace SAM

void build(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            pos[edges[i].to] = SAM::insert(edges[i].weight, pos[u]);
            build(edges[i].to, u);
        }
    head[u] = -1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &tid, &n), pos[1] = 1;
    for (int i = 1, u, v; i <= n - 1; i++)
    {
        scanf("%d%d%s", &u, &v, cmdlet + 1);
        addpath(u, v, cmdlet[1] - 'a');
        addpath(v, u, cmdlet[1] - 'a');
    }
    build(1, 0), scanf("%d", &q);
    while (q--)
    {
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
            printf("%lld\n", strtot);
        else if (opt == 2)
        {
            int rt, s;
            scanf("%d%d", &rt, &s);
            for (int i = 1, u, v; i <= s - 1; i++)
            {
                scanf("%d%d%s", &u, &v, cmdlet + 1);
                addpath(u, v, cmdlet[1] - 'a');
                addpath(v, u, cmdlet[1] - 'a');
            }
            build(rt, 0);
        }
        else
        {
            int p = 1;
            scanf("%s", cmdlet + 1);
            for (int i = 1; cmdlet[i]; i++)
                p = SAM::nodes[p].ch[cmdlet[i] - 'a'];
            if (p == 0)
                puts("0");
            else
                LCT::update(p), printf("%lld\n", LCT::val[p]);
        }
    }
    return 0;
}