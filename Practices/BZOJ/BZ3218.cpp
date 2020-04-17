// BZ3218.cpp
#include <bits/stdc++.h>

using namespace std;

const int LOG = 30, MAX_RN = 5e4 + 200, MAX_N = ((MAX_RN + 1) << 1) + MAX_RN * LOG, MAX_E = 3 * MAX_RN + MAX_RN * LOG, INF = 0x3f3f3f3f;

typedef long long ll;

int n, ai[MAX_RN], bi[MAX_RN], wi[MAX_RN], li[MAX_RN], ri[MAX_RN], pi[MAX_RN], head[MAX_N], current, dep[MAX_N], ptot;
int start_pos, end_pos, cur[MAX_N], upper, roots[MAX_RN];
vector<int> mp;

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

struct node
{
    int lson, rson;
} nodes[MAX_RN * 30];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (l == r)
    {
        if (pre != 0)
            addtube(p, pre, INF);
        addtube(p, val, INF);
        return p;
    }
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
    if (nodes[p].lson)
        addtube(p, nodes[p].lson, INF);
    if (nodes[p].rson)
        addtube(p, nodes[p].rson, INF);
    return p;
}

void link(int ql, int qr, int l, int r, int p, int src)
{
    if (p == 0)
        return;
    if (ql <= l && r <= qr)
        return (void)(addtube(src, p, INF));
    if (ql <= mid)
        link(ql, qr, l, mid, nodes[p].lson, src);
    if (mid < qr)
        link(ql, qr, mid + 1, r, nodes[p].rson, src);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (flow == 0 || u == end_pos)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

ll dinic()
{
    ll ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (ll di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d%d%d%d", &ai[i], &bi[i], &wi[i], &li[i], &ri[i], &pi[i]);
        mp.push_back(ai[i]), mp.push_back(li[i]), mp.push_back(ri[i]), ans += bi[i] + wi[i];
    }
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    ptot = (n + 1) << 1, start_pos = (n << 1) | 1, end_pos = start_pos + 1, upper = mp.size();
    for (int i = 1; i <= n; i++)
        addtube(start_pos, i, bi[i]), addtube(i, end_pos, wi[i]), addtube(i, i + n, pi[i]);
    for (int i = 1; i <= n; i++)
    {
        if (i > 1)
            link(ripe(li[i]), ripe(ri[i]), 1, upper, roots[i - 1], i + n);
        roots[i] = update(ripe(ai[i]), 1, upper, roots[i - 1], i);
    }
    printf("%lld\n", ans - dinic());
    return 0;
}