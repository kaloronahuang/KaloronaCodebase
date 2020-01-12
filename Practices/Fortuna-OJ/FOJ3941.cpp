// FOJ3941.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20010, MAX_E = 101000;
typedef pair<int, int> pii;

int head[MAX_N], current, n, m, distances[2][MAX_N], ui[MAX_E], vi[MAX_E], wi[MAX_E];
int ans[MAX_E], dfn[MAX_N], low[MAX_N], ptot;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src, int *dist)
{
    memset(dist, 0x3f, sizeof(int) * MAX_N);
    memset(vis, false, sizeof(vis));
    priority_queue<pii> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight != fa)
        {
            if (dfn[edges[i].to] == 0)
            {
                tarjan(edges[i].to, edges[i].weight), low[u] = min(low[u], low[edges[i].to]);
                if (low[edges[i].to] > dfn[u])
                    // cut;
                    ans[edges[i].weight] = 1;
            }
            else
                low[u] = min(low[u], dfn[edges[i].to]);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), ui[i] = u, vi[i] = v, wi[i] = w;
    shortest_path(1, distances[0]), shortest_path(n, distances[1]);
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        for (int rd = 0; rd <= 1; rd++)
        {
            if (distances[0][ui[i]] + distances[1][vi[i]] + wi[i] == distances[0][n])
            {
                addpath(ui[i], vi[i], i), addpath(vi[i], ui[i], i);
                break;
            }
            swap(ui[i], vi[i]);
        }
    // go for tarjan;
    tarjan(1, -1);
    int answer = 0;
    for (int i = 1; i <= m; i++)
        answer += ans[i];
    printf("%d\n", answer);
    for (int i = 1; i <= m; i++)
        if (ans[i])
            printf("%d ", i);
    return 0;
}