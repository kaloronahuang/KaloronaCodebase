// P3556.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int head[MAX_N], current, n, m, q;
short dist[MAX_N][MAX_N << 1];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 3];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void bfs(int src)
{
    queue<int> q;
    q.push(src), dist[src][src] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[src][edges[i].to] == 0)
                dist[src][edges[i].to] = dist[src][u] + 1, q.push(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v + n), addpath(v, u + n), addpath(v + n, u), addpath(u + n, v);
    for (int i = 1; i <= n; i++)
        if (head[i] != -1)
            bfs(i);
    while (q--)
    {
        int x, y, len;
        scanf("%d%d%d", &x, &y, &len);
        if (x == y && len == 0)
            puts("TAK");
        else
        {
            int di = dist[x][y + (len & 1) * n] - 1;
            if (di >= 0 && len >= di)
                puts("TAK");
            else
                puts("NIE");
        }
    }
    return 0;
}