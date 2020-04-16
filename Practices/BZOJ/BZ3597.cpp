// BZ3597.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_M = 3030;

const double eps = 1e-8;

int n, m, head[MAX_N], current;
double dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

bool spfa(int u, double mid)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dist[edges[i].to] > dist[u] + edges[i].weight + mid)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight + mid;
            if (vis[edges[i].to] || spfa(edges[i].to, mid))
                return true;
        }
    vis[u] = false;
    return false;
}

bool check(double mid)
{
    for (int i = 0; i <= n + 2; i++)
        dist[i] = 0, vis[i] = false;
    for (int i = 1; i <= n + 2; i++)
        if (spfa(i, mid))
            return true;
    return false;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, a, b, c, d; i <= m; i++)
    {
        scanf("%d%d%d%d%d%d", &u, &v, &a, &b, &c, &d), addpath(u, v, b + d);
        if (c > 0)
            addpath(v, u, a - d);
    }
    double l = 0, r = 5e4, res;
    while (l + eps < r)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid + eps, res = mid;
        else
            r = mid - eps;
    }
    printf("%.2lf\n", res);
    return 0;
}