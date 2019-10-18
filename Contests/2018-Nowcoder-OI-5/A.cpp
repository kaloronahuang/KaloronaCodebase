// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 200;

int head[MAX_N], current, n, m, answer[MAX_N], dist[MAX_N];
int srcs[MAX_N << 3], dsts[MAX_N << 3], weights[MAX_N << 3];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, id;
} edges[MAX_N << 3];

void addpath(int src, int dst, int weight, int id)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].id = id, edges[current].weight = weight;
    head[src] = current++;
}

void spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(0), dist[0] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (vis[edges[i].to] == false)
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    memset(answer, 0x3f, sizeof(answer));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w, i), srcs[i] = u, dsts[i] = v, weights[i] = w;
    for (int i = 1; i <= n; i++)
        addpath(0, i, 0, m + i);
    spfa();
    for (int i = 1; i <= m; i++)
        printf("%d %d %d\n", srcs[i], dsts[i], dist[srcs[i]] + weights[i] - dist[dsts[i]]);
    return 0;
}