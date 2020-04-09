// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_M = 4e5 + 200, INF = 0x3f3f3f3f;

typedef long long ll;

int T, n, p, q, head[MAX_N], current, start_pos, end_pos, dep[MAX_N], cur[MAX_N], W;
int absmat[550][550], udtable[550][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (flow == 0 || u == end_pos)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
        {
            int di = dfs(edges[i].to, min(flow, edges[i].weight));
            if (di > 0)
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
        }
    return 0;
}

int dinic()
{
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), memset(udtable, 0, sizeof(udtable)), memset(absmat, 0, sizeof(absmat));
        scanf("%d%d%d%d", &n, &W, &p, &q), current = 0;
        start_pos = n + 1, end_pos = n + 2;
        for (int i = 1, x, y, z, a, b, c, d, e, f; i <= p; i++)
        {
            scanf("%d%d%d%d%d%d%d%d%d", &x, &y, &z, &a, &b, &c, &d, &e, &f);
            absmat[x][y] += (a << 1), absmat[y][x] = absmat[x][y];
            absmat[y][z] += (b << 1), absmat[z][y] = absmat[y][z];
            absmat[z][x] += (c << 1), absmat[x][z] = absmat[z][x];
            udtable[x][0] += (d - f), udtable[x][1] -= (d - f);
            udtable[y][0] += (e - d), udtable[y][1] -= (e - d);
            udtable[z][0] += (f - e), udtable[z][1] -= (f - e);
        }
        for (int i = 1; i <= n; i++)
            udtable[i][0]++, udtable[i][1]--;
        for (int i = 1, x, y, r; i <= q; i++)
        {
            scanf("%d%d%d", &x, &y, &r);
            if (r == 0)
                addtube(y, x, INF);
            else if (r == 1)
                addtube(x, y, INF), addtube(y, x, INF);
            else
                udtable[x][0] = udtable[y][1] = INF;
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int tmp = min({udtable[i][0], udtable[i][1], 0});
            ans += tmp, addtube(start_pos, i, udtable[i][0] - tmp), addtube(i, end_pos, udtable[i][1] - tmp);
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (absmat[i][j] != 0)
                    addtube(i, j, absmat[i][j]);
        ans += dinic(), printf("%lld\n", 1LL * W * ans);
    }
    return 0;
}