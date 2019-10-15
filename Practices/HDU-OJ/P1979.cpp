// P1979.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, q, head[900 * 900 + 200], pos[40][40], ptot;
int stat[910][910], stot, current, dist[900 * 900 + 200];
bool mp[33][33], vis[900 * 900 + 200];

struct edge
{
    int to, nxt;
} edges[900 * 900 * 4 * 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void shortest_path(int src)
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u] == true)
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + 1)
                dist[edges[i].to] = dist[u] + 1, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1, tmp; j <= m; j++)
        {
            scanf("%d", &tmp), mp[i][j] = (tmp == 1);
            if (tmp == 1)
                pos[i][j] = ++ptot;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j])
                for (int x = 1; x <= n; x++)
                    for (int y = 1; y <= m; y++)
                        if (mp[x][y])
                            stat[pos[i][j]][pos[x][y]] = ++stot;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j])
                for (int x = 1; x <= n; x++)
                    for (int y = 1; y <= m; y++)
                        if (mp[x][y])
                        {
                            int blank = pos[i][j], chess = pos[x][y], id = stat[blank][chess];
                            // the blank moves;
                            if (pos[i - 1][j] != 0)
                                addpath(id, stat[pos[i - 1][j]][chess]);
                            if (pos[i][j - 1] != 0)
                                addpath(id, stat[pos[i][j - 1]][chess]);
                            if (pos[i + 1][j] != 0)
                                addpath(id, stat[pos[i + 1][j]][chess]);
                            if (pos[i][j + 1] != 0)
                                addpath(id, stat[pos[i][j + 1]][chess]);
                            // the chess moves;
                            if (abs(i - x) + abs(j - y) == 1)
                                addpath(id, stat[chess][blank]);
                        }
    while (q--)
    {
        int EX, EY, SX, SY, TX, TY;
        scanf("%d%d%d%d%d%d", &EX, &EY, &SX, &SY, &TX, &TY);
        shortest_path(stat[pos[EX][EY]][pos[SX][SY]]);
        int ans = INF;
        ans = min(ans, min(dist[stat[pos[TX - 1][TY]][pos[TX][TY]]], min(dist[stat[pos[TX + 1][TY]][pos[TX][TY]]], min(dist[stat[pos[TX][TY + 1]][pos[TX][TY]]], dist[stat[pos[TX][TY - 1]][pos[TX][TY]]]))));
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}