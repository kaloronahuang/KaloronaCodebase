// P2860.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5100, MAX_M = 10010;

int head[MAX_N], current, tot, dfn[MAX_N], low[MAX_N], aff[MAX_N], aff_tot;
int n, m, deg[MAX_N], sr[MAX_M], ds[MAX_N];
struct edge
{
    int to, nxt, stat;
} edges[MAX_M << 1];
stack<int> st;

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].stat = true, head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++tot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].stat)
            if (dfn[edges[i].to])
                low[u] = min(low[u], dfn[edges[i].to]);
            else
            {
                st.push(edges[i].to);
                edges[i].stat = false, edges[i ^ 1].stat = false;
                tarjan(edges[i].to);
                edges[i].stat = true, edges[i ^ 1].stat = true;
                low[u] = min(low[u], low[edges[i].to]);
            }
    if (dfn[u] == low[u])
    {
        aff_tot++;
        while (!st.empty())
        {
            aff[st.top()] = aff_tot;
            if (st.top() == u)
            {
                st.pop();
                break;
            }
            st.pop();
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &sr[i], &ds[i]), addpath(sr[i], ds[i]), addpath(ds[i], sr[i]);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            aff_tot = 0, st.push(i), tarjan(edges[i].to);
    for (int i = 1; i <= m; i++)
        if (aff[sr[i]] != aff[ds[i]])
            deg[aff[sr[i]]]++, deg[aff[ds[i]]]++;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            ans++;
    printf("%d", (ans + 1) / 2);
    return 0;
}