// flow.cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAX_N = 3030, MAX_M = 1e5 + 20, bitnum = 133;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, ecc[MAX_N], etot, mem[MAX_N], stk[MAX_N], tail;
ull str[MAX_N];
bool tag[MAX_M << 1];

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (tag[i] == false)
            if (dfn[edges[i].to] == 0)
                tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            else if (edges[i].to != fa)
                low[u] = min(low[u], dfn[edges[i].to]);
    if (low[u] == dfn[u])
    {
        etot++;
        do
        {
            ecc[stk[tail]] = etot;
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addpath(u, v), addpath(v, u);
        if (find(u) != find(v))
            mem[find(u)] = find(v);
    }
    for (int i = 1; i <= n; i++)
        str[i] = 1;
    for (int e = 0; e <= m; e++)
    {
        memset(dfn, 0, sizeof(dfn)), memset(low, 0, sizeof(low));
        memset(ecc, 0, sizeof(ecc));
        etot = 0, ptot = 0;
        if (e != m)
            tag[e << 1] = tag[e << 1 | 1] = true;
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0)
                tarjan(i, 0);
        for (int i = 1; i <= n; i++)
            str[i] = str[i] * bitnum + ecc[i];
        tag[e << 1] = tag[e << 1 | 1] = false;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            if (find(i) != find(j))
                continue;
            if (ecc[i] != ecc[j])
                ans += 1;
            else if (str[i] == str[j])
                ans += 3;
            else
                ans += 2;
        }
    printf("%lld\n", ans);
    return 0;
}