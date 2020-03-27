// CF715B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2010, MAX_M = 2e4 + 200;

typedef pair<int, int> pii;

int n, m, L, start_pt, end_pt, head[MAX_N], current, ui[MAX_M], vi[MAX_M], wi[MAX_M];
int dist[2][MAX_N];

bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &m, &L, &start_pt, &end_pt);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &ui[i], &vi[i], &wi[i]);
        addpath(ui[i], vi[i], i), addpath(vi[i], ui[i], i);
    }
    memset(dist[0], 0x3f, sizeof(dist[0])), memset(dist[1], 0x3f, sizeof(dist[1]));
    priority_queue<pii> pq;
    dist[1][end_pt] = dist[0][start_pt] = 0, pq.push(make_pair(0, end_pt));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[1][u] + max(1, wi[edges[i].weight]) < dist[1][edges[i].to])
                dist[1][edges[i].to] = dist[1][u] + max(1, wi[edges[i].weight]), pq.push(make_pair(-dist[1][edges[i].to], edges[i].to));
    }
    memset(vis, false, sizeof(vis)), pq.push(make_pair(0, start_pt));
    while (!pq.empty())
    {
        int u = pq.top().second, verdict = -pq.top().first;
        pq.pop();
        if (dist[0][u] < verdict)
            continue;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            if (wi[edges[i].weight] == 0)
                wi[edges[i].weight] = max(1, L - dist[1][edges[i].to] - dist[0][u]);
            if (dist[0][edges[i].to] > dist[0][u] + wi[edges[i].weight])
                dist[0][edges[i].to] = dist[0][u] + wi[edges[i].weight], pq.push(make_pair(-dist[0][edges[i].to], edges[i].to));
        }
    }
    if (dist[0][end_pt] != L)
        puts("NO");
    else
    {
        puts("YES");
        for (int i = 1; i <= m; i++)
            printf("%d %d %d\n", ui[i], vi[i], max(1, wi[i]));
    }

    return 0;
}