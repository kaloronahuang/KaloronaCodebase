// POJ1201.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_N = 50010;

int head[MAX_N], current, m, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void spfa()
{
    for (int i = 0; i < MAX_N; i++)
        dist[i] = -0x3f3f3f3f;
    queue<int> q;
    q.push(0), dist[0] = 0;
    vis[0] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] < dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &m);
    for (int i = 0; i <= 50000; i++)
    {
        // preprocess;
        addpath(i, i + 1, 0);
        addpath(i + 1, i, -1);
    }
    for (int i = 1, u, v, c; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &c);
        addpath(u, v + 1, c);
    }
    spfa();
    printf("%d", dist[50001]);
    return 0;
}