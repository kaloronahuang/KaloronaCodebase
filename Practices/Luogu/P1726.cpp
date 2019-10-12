// P1726.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_E = 5e4 + 200;

int n, m, head[MAX_N], current, ncnt, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
bool inst[MAX_N];
vector<int> blocks[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool compare(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size())
        return a.size() < b.size();
    int siz = a.size();
    for (int i = 0; i < siz; i++)
        if (a[i] != b[i])
            return a[i] > b[i];
    return false;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[edges[i].to], low[u]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ++ncnt;
        do
        {
            blocks[ncnt].push_back(stk[tail]), inst[stk[tail]] = false;
        } while (stk[tail--] != u);
        sort(blocks[ncnt].begin(), blocks[ncnt].end());
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, t; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &t);
        addpath(u, v);
        if (t == 2)
            addpath(v, u);
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    vector<int> &now = blocks[1];
    for (int i = 2; i <= ncnt; i++)
        if (compare(now, blocks[i]))
            now = blocks[i];
    printf("%lld\n", now.size());
    for (int i = 0, siz = now.size(); i < siz; i++)
        printf("%d ", now[i]);
    return 0;
}