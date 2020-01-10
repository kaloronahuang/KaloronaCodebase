// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int n, head[MAX_N], current;
double ri[MAX_N];
bool vis[MAX_N][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

struct point
{
    double x, y;
} pts[MAX_N];

double pow2(double x) { return x * x; }

double getDist(point &a, point &b) { return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y)); }

bool judge(point &a, point &b, point &c, point &d)
{
    double u, v, w, z;
    u = (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
    v = (d.x - a.x) * (b.y - a.y) - (b.x - a.x) * (d.y - a.y);
    w = (a.x - c.x) * (d.y - c.y) - (d.x - c.x) * (a.y - c.y);
    z = (b.x - c.x) * (d.y - c.y) - (d.x - c.x) * (b.y - c.y);
    return (u * v <= 0.00001 && w * z <= 0.00001);
}

void dfs(int u, int fa, int opt)
{
    if (vis[u][opt])
        return;
    vis[u][opt] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, opt ^ edges[i].weight);
}

int main()
{
    point remote_point = {9024.0, 6002.0};
    while (scanf("%d", &n) != EOF)
    {
        memset(head, -1, sizeof(head)), current = 0;
        for (int i = 1; i <= n + 1; i++)
            scanf("%lf%lf%lf", &pts[i].x, &pts[i].y, &ri[i]);
        for (int i = 1; i <= n; i++)
            ri[i] += ri[n + 1];
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (getDist(pts[i], pts[j]) < ri[i] + ri[j])
                    if (judge(pts[i], pts[j], pts[n + 1], remote_point))
                        addpath(i, j, 1), addpath(j, i, 1);
                    else
                        addpath(i, j, 0), addpath(j, i, 0);
        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, false, sizeof(vis));
            dfs(i, 0, 0);
            for (int j = 1; j <= n; j++)
                if (vis[j][0] && vis[j][1])
                {
                    flag = false;
                    break;
                }
            if (flag == false)
                break;
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}