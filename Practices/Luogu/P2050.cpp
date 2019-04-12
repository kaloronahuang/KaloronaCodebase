// P2050.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 100005, MAX_E = 1e7 + 2000;
int head[MAX_N], cur[MAX_N], current, dist[MAX_N], s, t, n, m, sum;
int pi[MAX_N], timCst[110][50], cook[MAX_N], order[MAX_N], upward[MAX_N];
int flow[MAX_N], answer;
bool inqu[MAX_N];
struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_E];
void addpath(int src, int dst, int weight, int cst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cst;
    head[src] = current++;
}
void add(int src, int dst, int weight, int cst)
{
    addpath(src, dst, weight, cst);
    addpath(dst, src, 0, -cst);
}
bool bfs()
{
    memset(dist, 0x3f, sizeof(dist));
    memset(upward, -1, sizeof(upward));
    queue<int> q;
    q.push(s), dist[s] = 0, inqu[s] = true, flow[s] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), inqu[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                upward[edges[i].to] = i;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!inqu[edges[i].to])
                    q.push(edges[i].to), inqu[edges[i].to] = true;
            }
    }
    if (upward[t] == -1)
        return false;
    int u = t;
    while (u != s)
    {
        int i = upward[u];
        edges[i].weight -= flow[t], edges[i ^ 1].weight += flow[t];
        answer += flow[t] * edges[i].cost, u = edges[i ^ 1].to;
    }
    return true;
}
int main()
{
    memset(head, -1, sizeof(head));
    //// Input;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), sum += pi[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &timCst[j][i]);
    //// Initialize;
    s = 0, t = n + sum * m + 1;

    //// Build the network;
    for (int i = 1; i <= n; i++)
        add(s, i, pi[i], 0);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            add(j, n + (i - 1) * sum + 1, 1, timCst[i][j]);
    // The last adding edges;
    for (int i = 1; i <= m; i++)
        add(n + (i - 1) * sum + 1, t, 1, 0);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= sum; j++)
        {
            int to = (i - 1) * sum + j + n;
            order[to] = j, cook[to] = i;
        }
    while (bfs())
    {
        int tmp = edges[upward[t] ^ 1].to;
        add(tmp + 1, t, 1, 0);
        for (int i = 1; i <= n; i++)
            add(i, tmp + 1, 1, timCst[cook[tmp]][i] * (order[tmp] + 1));
    }
    printf("%d", answer);
    return 0;
}