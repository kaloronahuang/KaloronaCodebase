// CF1063B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2010, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

typedef pair<int, int> pii;

int n, m, sx, sy, xlimit, ylimit, head[MAX_N * MAX_N], current, dist[MAX_N * MAX_N];
char mp[MAX_N][MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int getId(int x, int y) { return y + (x - 1) * m; }

bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pii> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
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
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &xlimit, &ylimit);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] != '*')
                for (int d = 0; d < 4; d++)
                    if (check(i + dx[d], j + dy[d]) && mp[i + dx[d]][j + dy[d]] != '*')
                        addpath(getId(i, j), getId(i + dx[d], j + dy[d]), dy[d] != 0);
    shortest_path(getId(sx, sy));
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (dist[getId(i, j)] == 0)
                ans++;
            else if (dist[getId(i, j)] != 0x3f3f3f3f)
            {
                // analyze;
                int ydist = abs(j - sy), cost1 = xlimit, cost2 = ylimit;
                if (j > sy)
                    swap(cost1, cost2);
                int d = (dist[getId(i, j)] - ydist) >> 1;
                if (cost1 >= ydist + d && cost2 >= d)
                    ans++;
            }
    printf("%d\n", ans);
    return 0;
}