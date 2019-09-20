// P2294.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110000, MAX_M = 1100000;

int head[MAX_N], current, n, m, T, cnt[MAX_N], dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool spfa(int st)
{
    for (int i = 1; i <= n; i++)
        dist[i] = -0x3f3f3f3f;
    queue<int> q;
    q.push(st), dist[st] = 0, vis[st] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        if (++cnt[u] == n)
            return false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] < dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(cnt, 0, sizeof(cnt)), memset(vis, false, sizeof(vis));
        memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        for (int i = 1, s, t, v; i <= m; i++)
            scanf("%d%d%d", &s, &t, &v), addpath(s - 1, t, v), addpath(t, s - 1, -v);

        for (int i = 0; i <= n; i++)
            if (cnt[i] == 0 && !spfa(i))
            {
                puts("false");
                goto gotonxt;
            }
        puts("true");
    gotonxt:
        continue;
    }
    return 0;
}