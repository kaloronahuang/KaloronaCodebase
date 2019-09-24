// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int n, xi[MAX_N], yi[MAX_N], head[MAX_N], current, a, b, c, d, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), n++;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int i = 2; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    double ub = double(c) / double(d), lb = double(a) / double(b);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && xi[i] < xi[j] && yi[i] < yi[j])
            {
                double angle = double(yi[j] - yi[i]) / double(xi[j] - xi[i]);
                if (lb < angle && angle < ub)
                    addpath(i, j);
            }
    // run spfa;
    queue<int> q;
    q.push(1), vis[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] < dist[u] + 1)
            {
                dist[edges[i].to] = dist[u] + 1;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dist[i]);
    printf("%d", ans);
    return 0;
}