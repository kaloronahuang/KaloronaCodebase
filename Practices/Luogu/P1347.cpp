// P1347.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30, MAX_E = 1e5 + 200;

int head[MAX_N], n, m, current, dist[MAX_N], deg[MAX_N], deg_bak[MAX_N];
int gid, tot;
bool vis[MAX_N], enablings[MAX_N];
char opt[30];

struct edge
{
    int to, nxt;
} edges[MAX_E];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++, deg_bak[dst]++;
}

void output()
{
    memset(dist, 0, sizeof(dist)), memcpy(deg, deg_bak, sizeof(deg));
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0 && enablings[i])
            q.push(i), dist[i] = 1, printf("%c", i + 'A' - 1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            dist[edges[i].to] = max(dist[edges[i].to], dist[u] + 1);
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to), printf("%c", edges[i].to + 'A' - 1);
        }
    }
}

void toposort()
{
    memset(dist, 0, sizeof(dist));
    int gans = 0, sum = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0 && enablings[i])
            q.push(i), dist[i] = 1, sum++;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            dist[edges[i].to] = max(dist[edges[i].to], dist[u] + 1), gans = max(gans, dist[edges[i].to]);
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to), sum++;
        }
    }
    if (gans == n)
    {
        // found;
        printf("Sorted sequence determined after %d relations: ", gid), output();
        puts(".");
        exit(0);
    }
    if (sum != tot)
    {
        printf("Inconsistency found after %d relations.", gid);
        exit(0);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        gid = i;
        scanf("%s", opt + 1), addpath(opt[1] - 'A' + 1, opt[3] - 'A' + 1);
        if (enablings[opt[1] - 'A' + 1] == false)
            tot++, enablings[opt[1] - 'A' + 1] = true;
        if (enablings[opt[3] - 'A' + 1] == false)
            tot++, enablings[opt[3] - 'A' + 1] = true;
        memcpy(deg, deg_bak, sizeof(deg));
        toposort();
    }
    printf("Sorted sequence cannot be determined.");
    return 0;
}