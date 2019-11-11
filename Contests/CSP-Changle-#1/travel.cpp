// travel.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 55;

int T, n, m, gtime, head[MAX_N], current, dist[MAX_N][20010];
bool vis[MAX_N][20010];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void spfa(int loop)
{
    memset(dist, 0x3f, sizeof(dist));
    queue<pr> q;
    q.push(make_pair(1, 0)), dist[1][0] = 0;
    while (!q.empty())
    {
        int u = q.front().first, t = q.front().second;
        q.pop(), vis[u][t] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            int ptime = dist[u][t] + edges[i].weight, ptime_m = ptime % loop;
            if (dist[edges[i].to][ptime_m] > ptime)
            {
                dist[edges[i].to][ptime_m] = ptime;
                if (!vis[edges[i].to][ptime_m])
                    q.push(make_pair(edges[i].to, ptime_m)), vis[edges[i].to][ptime_m] = true;
            }
        }
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d%d", &n, &m, &gtime);
        for (int i = 1, u, v, w; i <= m; i++)
            scanf("%d%d%d", &u, &v, &w), u++, v++, addpath(u, v, w), addpath(v, u, w);
        if (head[1] == -1)
            puts("Impossible");
        else
        {
            int loop = 1e4 + 10;
            for (int i = head[1]; i != -1; i = edges[i].nxt)
                if (edges[i].weight < loop)
                    loop = edges[i].weight;
            loop <<= 1, spfa(loop);
            if (dist[n][gtime % loop] <= gtime)
                puts("Possible");
            else
                puts("Impossible");
        }
    }
    return 0;
}