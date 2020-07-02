// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, dx[2] = {0, 1}, dy[2] = {1, 0};

typedef pair<int, int> pii;

int n, m, idx[MAX_N][MAX_N], head[MAX_N * MAX_N], current, dist[MAX_N * MAX_N], start_pos;
char str[MAX_N][MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 3];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortestPath()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pii> pq;
    pq.push(make_pair(0, start_pos)), dist[start_pos] = 0;
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
        scanf("%s", str[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            idx[i][j] = m * (i - 1) + j;
    start_pos = n * m + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int d = 0; d < 2; d++)
            {
                int dstx = i + dx[d], dsty = j + dy[d];
                if (str[dstx][dsty] != 0)
                    if (str[i][j] == '.')
                        if (str[dstx][dsty] != str[i][j])
                            addpath(idx[i][j], idx[dstx][dsty], 1);
                        else
                            addpath(idx[i][j], idx[dstx][dsty], 0);
                    else
                        addpath(idx[i][j], idx[dstx][dsty], 0);
            }
    addpath(start_pos, idx[1][1], str[1][1] == '#');
    shortestPath(), printf("%d\n", dist[idx[n][m]]);
    return 0;
}