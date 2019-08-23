// P3163.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 100, INF = 0x3f3f3f3f;

int n, a1, a2, an, b1, b2, bn;
int head[MAX_N], current, dep[MAX_N], st, ed, cur[MAX_N];
char org_mp[60][60];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}
bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(st), dep[st] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
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
    int ans = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(st, INF))
            ans += di;
    }
    return ans;
}

bool solve()
{
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                if (org_mp[i][j] == 'O')
                    addtube(i + 2, j + 2, 2);
                else if (org_mp[i][j] == 'N')
                    addtube(i + 2, j + 2, INF);

    addtube(st, a1 + 2, an), addtube(a2 + 2, ed, an);
    addtube(st, b1 + 2, bn), addtube(b2 + 2, ed, bn);
    return dinic() == an + bn;
}

int main()
{
    while (scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) != EOF)
    {
        for (int i = 1; i <= n; i++)
            scanf("%s", org_mp[i] + 1);
        st = 1, ed = 2;
        a1++, a2++, b1++, b2++;
        an <<= 1, bn <<= 1;
        puts(solve() && (swap(a1, a2), solve()) ? "Yes" : "No");
    }
    return 0;
}