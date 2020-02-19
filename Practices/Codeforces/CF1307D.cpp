// CF1307D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, sp, distances[2][MAX_N], head[MAX_N], current, spf[MAX_N];
pair<int, int> prs[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void shortest_path(int src, int *dist)
{
    memset(dist, -1, sizeof(distances[0]));
    queue<int> q;
    q.push(src), dist[src] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] == -1)
                dist[edges[i].to] = dist[u] + 1, q.push(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &sp);
    for (int i = 1; i <= sp; i++)
        scanf("%d", &spf[i]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    shortest_path(1, distances[0]), shortest_path(n, distances[1]);
    for (int i = 1; i <= sp; i++)
        prs[i] = make_pair(distances[0][spf[i]] - distances[1][spf[i]], spf[i]);
    sort(prs + 1, prs + 1 + sp);
    int max_1 = -0x3f3f3f3f, ans = 0;
    for (int i = 1; i <= sp; i++)
        ans = max(ans, max_1 + distances[1][prs[i].second]), max_1 = max(max_1, distances[0][prs[i].second]);
    printf("%d\n", min(ans + 1, distances[0][n]));
    return 0;
}