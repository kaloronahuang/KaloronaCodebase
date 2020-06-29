// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 525020, MAX_NODE = MAX_N * 30;

int n, vi[MAX_N], roots[MAX_N], ptot;
vector<int> G[MAX_N];
long long ans;

struct node
{
    int ch[2], bpos, sum, val;
} nodes[MAX_NODE];

void pushup(int p)
{
    nodes[p].sum = nodes[p].val = 0;
    if (nodes[p].ch[0])
    {
        nodes[p].sum += nodes[nodes[p].ch[0]].sum;
        nodes[p].val ^= nodes[nodes[p].ch[0]].val;
    }
    if (nodes[p].ch[1])
    {
        nodes[p].sum += nodes[nodes[p].ch[1]].sum;
        nodes[p].val ^= ((nodes[nodes[p].ch[1]].sum & 1) << nodes[p].bpos) ^ nodes[nodes[p].ch[1]].val;
    }
}

void insert(int x, int p)
{
    if (nodes[p].bpos > 25)
        return (void)(nodes[p].sum++);
    if (x & (1 << nodes[p].bpos))
    {
        if (nodes[p].ch[1] == 0)
            nodes[nodes[p].ch[1] = ++ptot].bpos = nodes[p].bpos + 1;
        insert(x, nodes[p].ch[1]);
    }
    else
    {
        if (nodes[p].ch[0] == 0)
            nodes[nodes[p].ch[0] = ++ptot].bpos = nodes[p].bpos + 1;
        insert(x, nodes[p].ch[0]);
    }
    pushup(p);
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    nodes[x].sum += nodes[y].sum, nodes[x].val ^= nodes[y].val;
    nodes[x].ch[0] = merge(nodes[x].ch[0], nodes[y].ch[0]);
    nodes[x].ch[1] = merge(nodes[x].ch[1], nodes[y].ch[1]);
    return x;
}

void update(int p)
{
    swap(nodes[p].ch[0], nodes[p].ch[1]);
    if (nodes[p].ch[0])
        update(nodes[p].ch[0]);
    pushup(p);
}

void dfs(int u)
{
    roots[u] = ++ptot, nodes[ptot].bpos = 0;
    for (int v : G[u])
        dfs(v), roots[u] = merge(roots[u], roots[v]);
    update(roots[u]), insert(vi[u], roots[u]);
    ans += nodes[roots[u]].val;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &vi[i]);
    for (int i = 2, fa; i <= n; i++)
        scanf("%d", &fa), G[fa].push_back(i);
    dfs(1), printf("%lld\n", ans);
    return 0;
}