// CF241E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_E = 5050;

int n, m, head[MAX_N], current, ui[MAX_E], vi[MAX_E], dist[MAX_N], cnt[MAX_N];
bool vis[MAX_N], connectivity[2][MAX_N], included[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int typ)
{
    connectivity[typ][u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight == typ && connectivity[typ][edges[i].to] == false)
            dfs(edges[i].to, typ);
}

bool spfa()
{
    memset(dist, -0x3f, sizeof(dist));
    queue<int> q;
    q.push(1), vis[1] = true, dist[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), cnt[u]++, vis[u] = false;
        if (cnt[u] > m)
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
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &ui[i], &vi[i]), addpath(ui[i], vi[i], 0), addpath(vi[i], ui[i], 1);
    dfs(1, 0), dfs(n, 1);
    bool global_flag = false;
    for (int i = 1; i <= n; i++)
    {
        global_flag |= connectivity[0][i] && connectivity[1][i];
        included[i] = connectivity[0][i] && connectivity[1][i];
    }
    if (!global_flag)
        puts("No"), exit(0);
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        if (included[ui[i]] && included[vi[i]])
            addpath(ui[i], vi[i], 1), addpath(vi[i], ui[i], -2);
    if (!spfa())
        puts("No");
    else
    {
        puts("Yes");
        for (int i = 1; i <= m; i++)
            if (included[ui[i]] && included[vi[i]])
                printf("%d\n", dist[vi[i]] - dist[ui[i]]);
            else
                puts("1");
    }
    return 0;
}