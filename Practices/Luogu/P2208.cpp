// P2208.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 500 * 510;

int head[MAX_N << 1], current, n, m, st, ed, dist[MAX_N << 1];
char mat[550][550];
bool vis[MAX_N << 1];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int getId(int x, int y) { return (x - 1) * m + y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int mp_siz = n * m;
    for (int i = 1; i <= n; i++)
        scanf("%s", mat[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mat[i][j] != '#')
            {
                if (mat[i + 1][j] == '#' && i < n && mat[i - 1][j] != '#' && i > 1)
                    addpath(getId(i, j), getId(i - 1, j) + mp_siz, 1);
                if (mat[i + 1][j] != '#' && i < n)
                    addpath(getId(i, j), getId(i + 1, j), 0);
                else
                {
                    if (mat[i][j - 1] != '#' && j > 1)
                        addpath(getId(i, j), getId(i, j - 1), 0);
                    if (mat[i][j + 1] != '#' && j < n)
                        addpath(getId(i, j), getId(i, j + 1), 0);
                }
            }
            if (mat[i][j] == 'C')
                st = getId(i, j);
            if (mat[i][j] == 'D')
                ed = getId(i, j);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mat[i][j] != '#')
            {
                if (mat[i - 1][j] == '#' && i > 1 && mat[i + 1][j] != '#' && i < n)
                    addpath(getId(i, j) + mp_siz, getId(i + 1, j), 1);
                if (mat[i - 1][j] != '#' && i > 1)
                    addpath(getId(i, j) + mp_siz, getId(i - 1, j) + mp_siz, 0);
                else
                {
                    if (mat[i][j - 1] != '#' && j > 1)
                        addpath(getId(i, j) + mp_siz, getId(i, j - 1) + mp_siz, 0);
                    if (mat[i][j + 1] != '#' && j < n)
                        addpath(getId(i, j) + mp_siz, getId(i, j + 1) + mp_siz, 0);
                }
            }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, st)), dist[st] = 0;
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
    int ans = min(dist[ed], dist[ed + mp_siz]);
    if (ans == 0x3f3f3f3f)
        puts("-1");
    else
        printf("%d", ans);
    return 0;
}
