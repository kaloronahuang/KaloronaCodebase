// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 550, INF = 0x3f3f3f3f;

int n, m, dist[MAX_N * MAX_N], name[MAX_N][MAX_N], cx, cy, px, py;
int upper[MAX_N][MAX_N], lower[MAX_N][MAX_N], lft[MAX_N][MAX_N], rig[MAX_N][MAX_N];
int head[MAX_N * MAX_N], current;
char mp[MAX_N][MAX_N];
bool vis[MAX_N * MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N * 10];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void djisktra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    dist[name[cx][cy]] = 0;
    pq.push(make_pair(0, name[cx][cy]));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            name[i][j] = (i - 1) * m + j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == 'C')
                cx = i, cy = j;
            if (mp[i][j] == 'F')
                px = i, py = j;
            if (mp[i - 1][j] != '#')
                upper[i][j] = upper[i - 1][j];
            else
                upper[i][j] = i;
            if (mp[i][j - 1] != '#')
                lft[i][j] = lft[i][j - 1];
            else
                lft[i][j] = j;
        }

    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
        {
            if (mp[i + 1][j] != '#')
                lower[i][j] = lower[i + 1][j];
            else
                lower[i][j] = i;
            if (mp[i][j + 1] != '#')
                rig[i][j] = rig[i][j + 1];
            else
                rig[i][j] = j;
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] != '#')
            {
                addpath(name[i][j], name[i - 1][j], 1);
                addpath(name[i][j], name[i + 1][j], 1);
                addpath(name[i][j], name[i][j + 1], 1);
                addpath(name[i][j], name[i][j - 1], 1);

                int dist = min(i - upper[i][j], min(lower[i][j] - i, min(j - lft[i][j], rig[i][j] - j))) + 1;

                addpath(name[i][j], name[i][lft[i][j]], dist);
                addpath(name[i][j], name[i][rig[i][j]], dist);
                addpath(name[i][j], name[upper[i][j]][j], dist);
                addpath(name[i][j], name[lower[i][j]][j], dist);
            }

    djisktra();
    if (dist[name[px][py]] == INF)
        puts("no");
    else
        printf("%d", dist[name[px][py]]);
    return 0;
}