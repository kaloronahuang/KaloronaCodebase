// P5590.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 21010;

int head[MAX_N], current, dist[MAX_N], n, m, ui[MAX_N], vi[MAX_N], cnt[MAX_N];
bool vis1[MAX_N], visN[MAX_N], vis[MAX_N], tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void mark(int u, bool *vis_arr)
{
    vis_arr[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis_arr[edges[i].to])
            mark(edges[i].to, vis_arr);
}

bool spfa(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(src), vis[src] = true, cnt[src]++, dist[src] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (++cnt[u] > n)
                    return false;
                if (vis[edges[i].to] == false)
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return true;
}

int main()
{
    memset(head, -1, sizeof(head)), current = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &ui[i], &vi[i]), addpath(ui[i], vi[i], 0);
    mark(1, vis1);
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        addpath(vi[i], ui[i], 0);
    mark(n, visN);
    if (vis1[n] == false)
        puts("-1"), exit(0);
    for (int i = 1; i <= n; i++)
        tag[i] = vis1[i] && visN[i];
    tag[1] = tag[n] = true;
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        if (tag[ui[i]] && tag[vi[i]])
            addpath(ui[i], vi[i], 9), addpath(vi[i], ui[i], -1);
    if (!spfa(1))
        puts("-1"), exit(0);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= m; i++)
    {
        printf("%d %d ", ui[i], vi[i]);
        if (tag[ui[i]] && tag[vi[i]])
            printf("%d\n", dist[vi[i]] - dist[ui[i]]);
        else
            puts("1");
    }
    return 0;
}