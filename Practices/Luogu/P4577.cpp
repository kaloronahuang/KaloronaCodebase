// P4577.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, wi[MAX_N], head[MAX_N], current, ptot, roots[MAX_N];
vector<int> mp;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 50];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    nodes[x].sum += nodes[y].sum;
    nodes[x].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[x].rson = merge(nodes[x].rson, nodes[y].rson);
    return x;
}

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum++;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

void eliminate(int p)
{
    if (p == 0)
        return;
    nodes[p].sum--;
    if (nodes[nodes[p].rson].sum > 0)
        eliminate(nodes[p].rson);
    else
        eliminate(nodes[p].lson);
}

bool modify(int qx, int l, int r, int p)
{
    if (l == r)
        return false;
    int mid = (l + r) >> 1;
    bool ret = false;
    if (qx <= mid)
        ret |= modify(qx, l, mid, nodes[p].lson);
    else
    {
        ret |= modify(qx, mid + 1, r, nodes[p].rson);
        if (nodes[nodes[p].lson].sum && ret == false)
            ret = true, eliminate(nodes[p].lson);
    }
    if (ret)
        nodes[p].sum--;
    return ret;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to, u), merge(roots[u], roots[edges[i].to]);
    modify(wi[u], 1, n, roots[u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]), mp.push_back(wi[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        wi[i] = ripe(wi[i]), roots[i] = update(wi[i], 1, n, roots[i]);
    for (int i = 2, fat; i <= n; i++)
        scanf("%d", &fat), addpath(fat, i);
    dfs(1, 0), printf("%d\n", nodes[roots[1]].sum);
    return 0;
}