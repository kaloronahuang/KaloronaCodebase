// POJ3621.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 2020;
const double eps = 1e-4;

int n, m, val[MAX_N], current, head[MAX_N];
double dist[MAX_N];

struct edge
{
    int from, to, weight, nxt;
} edges[10100];
int vis[MAX_N], cnt;

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool dfs(int u, double mid)
{
    vis[u] = cnt;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        double w = mid * edges[i].weight - val[u];
        if (dist[edges[i].to] > dist[u] + w)
        {
            dist[edges[i].to] = dist[u] + w;
            if (vis[edges[i].to] == vis[u])
                return true;
            else if (dfs(edges[i].to, mid))
                return true;
        }
    }
    vis[u] = 0;
    return false;
}

bool check(double mid)
{
    memset(vis, 0, sizeof(vis));
    for (cnt = 1; cnt <= n; cnt++)
        if (dfs(cnt, mid))
            return true;
    return false;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w);
    double l = 0, r = 2000;
    while (fabs(r - l) > eps)
    {
        double mid = (l + r) / 2.0;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.2f", l);
    return 0;
}