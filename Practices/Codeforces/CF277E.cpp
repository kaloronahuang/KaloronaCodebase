// CF277E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

typedef pair<int, double> pid;

int n, m, head[MAX_N], current, flow[MAX_N], pre[MAX_N], start_pos, end_pos;
double dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
    double cost;
} edges[MAX_N * MAX_N << 2];

struct node
{
    int x, y;
} nodes[MAX_N];

void addpath(int src, int dst, int weight, double cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, double cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

double pow2(double x) { return x * x; }

double getDist(int x, int y) { return sqrt(pow2(nodes[x].x - nodes[y].x) + pow2(nodes[x].y - nodes[y].y)); }

bool spfa()
{
    fill(dist + 1, dist + 1 + end_pos, 1.0 * 0x3f3f3f3f3f3f3f3f);
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    memset(flow, 0x3f, sizeof(flow));
    queue<int> q;
    q.push(start_pos), dist[start_pos] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
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
    return pre[end_pos] != -1;
}

pid mfmc()
{
    int ret = 0;
    double cost = 0;
    while (spfa())
    {
        ret += flow[end_pos], cost += 1.0 * dist[end_pos] * flow[end_pos];
        int u = end_pos;
        while (u != start_pos)
        {
            edges[pre[u]].weight -= flow[end_pos], edges[pre[u] ^ 1].weight += flow[end_pos];
            u = edges[pre[u] ^ 1].to;
        }
    }
    return make_pair(ret, cost);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), start_pos = (n << 1) | 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &nodes[i].x, &nodes[i].y);
        addtube(start_pos, i, 2, 0);
        addtube(i + n, end_pos, 1, 0);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && nodes[i].y > nodes[j].y)
                addtube(i, j + n, 1, getDist(i, j));
    pid res = mfmc();
    if (res.first == n - 1)
        printf("%.10lf\n", res.second);
    else
        puts("-1");
    return 0;
}