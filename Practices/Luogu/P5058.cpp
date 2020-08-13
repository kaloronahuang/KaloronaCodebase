// P5058.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, MAX_E = 5e5 + 200;

int n, head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail, ctot, start_pos, end_pos;
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] >= dfn[u])
            {
                ctot++;
                while (true)
                {
                    int x = stk[tail--];
                    G[x].push_back(ctot), G[ctot].push_back(x);
                    // cerr << x << " " << ctot << endl;
                    if (x == edges[i].to)
                        break;
                }
                G[u].push_back(ctot), G[ctot].push_back(u);
                // cerr << ctot << " " << u << endl;
            }
        }
        else if (edges[i].to != fa)
            low[u] = min(low[u], dfn[edges[i].to]);
}

void dfs(int u, int fa, int acc)
{
    if (u == end_pos)
    {
        if (acc <= n)
            printf("%d\n", acc);
        else
            puts("No solution");
        return;
    }
    if (u <= n && G[u].size() > 1 && u != start_pos)
        acc = min(acc, u);
    for (int v : G[u])
        if (v != fa)
            dfs(v, u, acc);
}

int main()
{
    memset(head, -1, sizeof(head)), scanf("%d", &n), ctot = n;
    for (int i = 1, u, v;; i++)
    {
        scanf("%d%d", &u, &v);
        if (u == 0 && v == 0)
            break;
        addpath(u, v), addpath(v, u);
    }
    scanf("%d%d", &start_pos, &end_pos);
    tarjan(start_pos, 0);
    if (dfn[end_pos] == 0)
        puts("No solution"), exit(0);
    dfs(start_pos, 0, n + 1);
    return 0;
}