// weixiu.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 505050;

int n, m, head[MAX_N], current, dist[MAX_N], T;
bool vis[MAX_N];
char opt[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

inline int getId(int x, int y) { return (x - 1) * (m + 1) + y; }

priority_queue<pr> pq;

void djisktra()
{
    while (!pq.empty())
        pq.pop();
    memset(dist, 0x3f, sizeof(dist)), memset(vis, false, sizeof(vis));
    dist[1] = 0, pq.push(make_pair(0, 1));
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

int main()
{
    freopen("weixiu.in", "r", stdin);
    freopen("weixiu.out", "w", stdout);
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d", &n, &m);
        int ed = getId(n + 1, m + 1);
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", opt + 1);
            for (int j = 1; j <= m; j++)
                if (opt[j] == '\\')
                {
                    addpath(getId(i, j), getId(i + 1, j + 1), 0), addpath(getId(i + 1, j), getId(i, j + 1), 1);
                    addpath(getId(i + 1, j + 1), getId(i, j), 0), addpath(getId(i, j + 1), getId(i + 1, j), 1);
                }
                else
                {
                    addpath(getId(i, j), getId(i + 1, j + 1), 1), addpath(getId(i + 1, j), getId(i, j + 1), 0);
                    addpath(getId(i + 1, j + 1), getId(i, j), 1), addpath(getId(i, j + 1), getId(i + 1, j), 0);
                }
        }
        djisktra();
        if (dist[ed] == 0x3f3f3f3f)
            printf("NO SOLUTION\n");
        else
            printf("%d\n", dist[ed]);
    }
    return 0;
}