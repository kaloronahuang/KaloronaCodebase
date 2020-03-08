// LOJ6227.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, limit, head[MAX_N], current, pre[MAX_N], flow[MAX_N], start_pos, end_pos;
ll dist[MAX_N];
bool vis[MAX_N];
vector<int> vec;

struct seg
{
    int l, r, val;
} segs[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 2];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost) { addpath(src, dst, weight, cost), addpath(dst, src, 0, -cost); }

bool spfa_max(int src)
{
    memset(flow, 0x3f, sizeof(flow)), memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre)), memset(dist, 128, sizeof(dist));
    queue<int> q;
    q.push(src), vis[src] = true, dist[src] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] < dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return pre[end_pos] != -1;
}

ll mfmc()
{
    ll ret = 0;
    while (spfa_max(start_pos))
    {
        ret += 1LL * dist[end_pos] * flow[end_pos];
        int p = end_pos;
        while (p != start_pos)
            edges[pre[p]].weight -= flow[end_pos], edges[pre[p] ^ 1].weight += flow[end_pos], p = edges[pre[p] ^ 1].to;
    }
    return ret;
}

int ripe(int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &limit);
    for (int i = 1, y_1, y_2; i <= n; i++)
    {
        scanf("%d%d%d%d", &segs[i].l, &y_1, &segs[i].r, &y_2);
        segs[i].val = sqrt(1LL * (segs[i].r - segs[i].l) * (segs[i].r - segs[i].l) + 1LL * (y_1 - y_2) * (y_1 - y_2));
        vec.push_back(segs[i].l), vec.push_back(segs[i].r);
    }
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int upper = vec.size();
    start_pos = (upper << 1 | 1), end_pos = start_pos + 1;
    addtube(start_pos, 1, limit, 0);
    for (int i = 1; i < upper; i++)
        addtube(i, i + upper, limit, 0), addtube(i + upper, i + 1, limit, 0);
    addtube(upper, upper << 1, limit, 0), addtube(upper << 1, end_pos, limit, 0);
    for (int i = 1; i <= n; i++)
    {
        int x = ripe(segs[i].l), y = ripe(segs[i].r);
        if (x > y)
            swap(x, y);
        if (x == y)
            addtube(x, x + upper, 1, segs[i].val);
        else
            addtube(x + upper, y, 1, segs[i].val);
    }
    printf("%lld\n", mfmc());
    return 0;
}