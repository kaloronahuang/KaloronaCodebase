// LOJ6014.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, pre[MAX_N], dist[MAX_N];
int st, ed, flow[MAX_N], n, k, mx_range;
bool vis[MAX_N];
vector<int> vec;

struct segment
{
    int l, r;
} segs[MAX_N];

struct edge
{
    int to, weight, cost, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight, int cst)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].cost = cst, edges[current].nxt = head[src];
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cst)
{
    addpath(src, dst, weight, cst);
    addpath(dst, src, 0, -cst);
}

bool bfs()
{
    memset(dist, 0x3f, sizeof(dist)), memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(st), vis[st] = true, flow[st] = INF, dist[st] = 0;
    while (!q.empty())
    {
        int u = q.front();
        vis[u] = false;
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[ed] != INF;
}

int mcmf()
{
    long long ans = 0;
    while (bfs())
    {
        int p = ed, i = pre[p];
        ans += 1LL * flow[ed] * dist[ed];
        while (p != st)
        {
            edges[i].weight -= flow[ed], edges[i ^ 1].weight += flow[ed];
            p = edges[i ^ 1].to, i = pre[p];
        }
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &segs[i].l, &segs[i].r);
        if (segs[i].l > segs[i].r)
            swap(segs[i].l, segs[i].r);
        vec.push_back(segs[i].l), vec.push_back(segs[i].r);
    }
    vec.push_back(-0x3f3f3f3f);
    sort(vec.begin(), vec.end());
    st = 0, ed = 2 * n + 1;

    addtube(st, 1, k, 0);
    for (int i = 1; i < 2 * n; i++)
        addtube(i, i + 1, INF, 0);
    addtube(2 * n, ed, k, 0);

    for (int i = 1; i <= n; i++)
    {
        int len = segs[i].r - segs[i].l;
        segs[i].l = lower_bound(vec.begin(), vec.end(), segs[i].l) - vec.begin();
        segs[i].r = lower_bound(vec.begin(), vec.end(), segs[i].r) - vec.begin();
        addtube(segs[i].l, segs[i].r, 1, -len);
    }
    printf("%d", -mcmf());
    return 0;
}

