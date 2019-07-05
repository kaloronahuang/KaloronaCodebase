// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100, MAX_E = 1000500;

int head[MAX_N], current, n, m, dat[MAX_N], anses[MAX_E], deg[MAX_N], loopNum;
bool tag[MAX_N];

struct edge
{
    int id, to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int id)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].id = id, head[src] = current++;
}

void toposort()
{
    loopNum = n;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            q.push(i), loopNum--;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (deg[edges[i].to] != 0)
            {
                deg[u]--;
                if ((--deg[edges[i].to]) == 1)
                    q.push(edges[i].to), loopNum--;
                anses[edges[i].id] = 2 * (dat[u]);
                dat[edges[i].to] -= dat[u], dat[u] = 0;
            }
    }
}

void preprocess(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (deg[edges[i].to] && edges[i].to != fa && tag[i] == false)
        {
            tag[i] = true, preprocess(edges[i].to, u);
            return;
        }
}

void dfs(int u, int fa, int lastEdge, int dep)
{
    if (lastEdge != -1)
        anses[edges[lastEdge].id] += (dep & 1) ? dat[u] : -dat[u];
        
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (tag[i])
        {
            if (lastEdge == i)
                return;
            dfs(edges[i].to, u, ((lastEdge == -1) ? i : lastEdge), dep + 1);
            return;
        }
}

void calc(int u, int fa, int lastEdge, int dep)
{
    if (dep == loopNum)
        return;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (tag[i])
        {
            if (fa)
                anses[edges[i].id] = -(anses[edges[lastEdge].id] - dat[u]) + dat[u];
            calc(edges[i].to, u, i, dep + 1);
            return;
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &dat[i]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v, i), addpath(v, u, i), deg[u]++, deg[v]++;
    if (m > n)
    {
        puts("0");
        return 0;
    }
    toposort();
    if (m == n)
    {
        if (loopNum % 2 == 0)
        {
            puts("0");
            return 0;
        }
        for (int i = 1; i <= n; i++)
            if (deg[i] > 0)
            {
                preprocess(i, 0);
                dfs(i, 0, -1, 0);
                calc(i, 0, 0, 0);
                break;
            }
    }

    for (int i = 1; i <= m; i++)
        printf("%d\n", anses[i]);
    return 0;
}