// P3159.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 25 * 25 * 4, INF = 0x3f3f3f3f;
const int dirx[8] = {-1, 0, 1, -1, 1, -1, 0, 1}, diry[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int mi[25][25], head[MAX_N], current, dist[MAX_N];
int s, t, flow[MAX_N], pre[MAX_N], maxflow, mincost;
int n, m, source[25][25], destination[25][25];
bool vis[MAX_N];
string str;

struct edge
{
    int to, nxt, weight, cost;
} edges[992500];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void add(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist)), memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(s), flow[s] = INF, vis[s] = true;
    dist[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return dist[t] != INF;
}

void mfmc()
{
    while (spfa())
    {
        maxflow += flow[t], mincost += flow[t] * dist[t];
        int p = t;
        while (p != s)
        {
            edges[pre[p]].weight -= flow[t];
            edges[pre[p] ^ 1].weight += flow[t];
            p = edges[pre[p] ^ 1].to;
        }
    }
}

int getId(int x, int y, int id) { return (m * (x - 1) + y) * 3 - id; }

void print()
{
    for (int pt = s; pt <= t; pt++)
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            printf("%d %d %d&%d\n", pt, edges[i].to, edges[i].weight, edges[i].cost);
}

int main()
{
    memset(head, -1, sizeof(head));
    int totdst = 0, totsrc = 0;
    scanf("%d%d", &n, &m);
    s = 0, t = 3 * n * m + 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        for (int j = 0; j < m; j++)
            source[i][j + 1] = str[j] - '0';
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        for (int j = 0; j < m; j++)
            destination[i][j + 1] = str[j] - '0';
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        for (int j = 0; j < m; j++)
            mi[i][j + 1] = str[j] - '0';
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (source[i][j])
                add(s, getId(i, j, 1), 1, 0), totsrc++;
            if (destination[i][j])
                add(getId(i, j, 1), t, 1, 0), totdst++;
            add(getId(i, j, 0), getId(i, j, 1), (mi[i][j] + (!source[i][j] && destination[i][j])) / 2, 0);
            add(getId(i, j, 1), getId(i, j, 2), (mi[i][j] + (source[i][j] && !destination[i][j])) / 2, 0);
            for (int dir = 0; dir < 8; dir++)
            {
                int dstx = i + dirx[dir], dsty = j + diry[dir];
                if (dstx <= n && dstx >= 1 && dsty <= m && dsty >= 1)
                    add(getId(i, j, 2), getId(dstx, dsty, 0), INF, 1);
            }
        }
    }
    mfmc();
    if (totdst == totsrc && totdst == maxflow)
        printf("%d\n", mincost);
    else
        puts("-1");
    return 0;
}