// FOJ4037.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 2000;

// standard data of graph;
int head[MAX_N], current, n, q, siz[MAX_N];
// LCA backend;
int euler_tot, firstOccurence[MAX_N], euler_order[MAX_N << 1], rmq[20][MAX_N << 1], dep[MAX_N], prefix[MAX_N];
// divide & conquer;
bool tag[MAX_N];
// root stuff;
int max_son[MAX_N], root, general_root;

struct edge
{
    int to, weight, nxt;
} edges[MAX_N << 1];
// dq tree stuff;
vector<edge> dqGraph[MAX_N];
int dq_fa[MAX_N];
ll di[MAX_N], sum[MAX_N], sumq[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    edges[current].weight = weight, head[src] = current++;
}

void init_euler(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    euler_order[firstOccurence[u] = ++euler_tot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            prefix[edges[i].to] = prefix[u] + edges[i].weight;
            init_euler(edges[i].to, u), euler_order[++euler_tot] = u;
        }
}

void init_rmq()
{
    for (int i = 1; i <= euler_tot; i++)
        rmq[0][i] = euler_order[i];
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= euler_tot - (1 << i) + 1; j++)
        {
            int x = rmq[i - 1][j], y = rmq[i - 1][j + (1 << (i - 1))];
            rmq[i][j] = (dep[x] > dep[y]) ? y : x;
        }
}

int dist(int x, int y)
{
    int l = firstOccurence[x], r = firstOccurence[y];
    if (l > r)
        swap(l, r);
    int len = log2(r - l + 1), lca1 = rmq[len][l], lca2 = rmq[len][r - (1 << len) + 1];
    int lca = (dep[lca1] < dep[lca2]) ? lca1 : lca2;
    return prefix[x] + prefix[y] - (prefix[lca] << 1);
}

void updateSize(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            updateSize(edges[i].to, u), siz[u] += siz[edges[i].to];
}

void __find_root(int u, int fa, int fake_root)
{
    max_son[u] = siz[fake_root] - siz[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            max_son[u] = max(max_son[u], siz[edges[i].to]);
    if (max_son[u] < max_son[root])
        root = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            __find_root(edges[i].to, u, fake_root);
}

void find_root(int u) { updateSize(u, 0), root = u, __find_root(u, 0, u); }

int build_dq_tree(int u, int fa)
{
    find_root(u);
    if (general_root == 0)
        general_root = root;
    tag[root] = true, dq_fa[root] = fa;
    int pt = root;
    for (int i = head[root]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            int dest = build_dq_tree(edges[i].to, pt);
            dqGraph[pt].push_back(edge{dest, edges[i].to, -1});
        }
    return pt;
}

void update(int u, int delta)
{
    int curt = u;
    di[u] += delta;
    while (u)
    {
        sum[u] += delta;
        sumq[u] += 1LL * delta * dist(curt, dq_fa[u] ? dq_fa[u] : u);
        u = dq_fa[u];
    }
}

ll move_station(int src, int dst, int channel)
{
    ll ans = 0, cnt = di[src];
    for (int i = 0, siz = dqGraph[src].size(); i < siz; i++)
    {
        int v = dqGraph[src][i].to;
        if (v != dst)
            ans += sumq[v], cnt += sum[v];
    }
    di[channel] += cnt;
    return ans + cnt * dist(src, channel);
}

ll query(ll ans, int u)
{
    for (int i = 0, siz = dqGraph[u].size(); i < siz; i++)
    {
        int v = dqGraph[u][i].to;
        if ((sum[v] << 1) > sum[u])
        {
            // consider to move the station;
            ll channel = dqGraph[u][i].weight, pre = di[channel], tmp, delta = move_station(u, v, channel);
            tmp = di[channel] - pre;
            for (int pt = channel; pt != u; pt = dq_fa[pt])
                sum[pt] += tmp, sumq[pt] += tmp * dist(channel, dq_fa[pt] ? dq_fa[pt] : pt);
            ll nans = 0;
            for (int j = 0, siz2 = dqGraph[v].size(), dst; j < siz2; j++)
                dst = dqGraph[v][j].to, nans += sumq[dst];
            ans = delta + query(nans, v);
            for (int pt = channel; pt != u; pt = dq_fa[pt])
                sum[pt] -= tmp, sumq[pt] -= tmp * dist(channel, dq_fa[pt] ? dq_fa[pt] : pt);
            di[channel] = pre;
            return ans;
        }
    }
    return ans;
}

int main()
{
    // graph construction;
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    // initialization;
    init_euler(1, 0), init_rmq(), build_dq_tree(1, 0);
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y), update(x, y);
        printf("%lld\n", query(sumq[general_root], general_root));
    }
    return 0;
}
