// BZ3470.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_E = 1e5 + 200;

int n, m, head[MAX_N], current, deg[MAX_N], idx[MAX_N], itot;
double g[MAX_N], acc[MAX_N], f[MAX_N], acc_w[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), idx[++itot] = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), u++, v++, addpath(u, v, w), deg[v]++;
    toposort(), g[1] = 1;
    for (int i = 1; i <= n; i++)
    {
        int u = idx[i], sum = 0;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            sum += edges[i].weight;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            g[edges[i].to] += 1.0 * g[u] * edges[i].weight / sum;
    }
    memset(deg, 0, sizeof(deg));
    for (int i = n; i >= 1; i--)
    {
        int u = idx[i];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            acc[u] += edges[i].weight * f[edges[i].to], acc_w[u] += edges[i].weight, deg[u]++;
        if (acc_w[u] > 0)
            f[u] = acc[u] / acc_w[u] + 1;
    }
    double ans = f[1];
    for (int i = n; i >= 1; i--)
    {
        int u = idx[i];
        if (deg[u] <= 1)
            continue;
        double curt = f[1] - g[u] * f[u];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            double A = acc[u] - edges[i].weight * f[edges[i].to], B = acc_w[u] - edges[i].weight;
            ans = max(ans, curt + g[u] * (A / B + 1));
        }
    }
    printf("%.6lf\n", ans);
    return 0;
}