// P3573.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200, MAX_E = 3e6 + 200;

int head[MAX_N], current, n, m, topo_order[MAX_N], indeg[MAX_N];
int atTail[MAX_N], atBegin[MAX_N];
multiset<int> ms;
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

void toposort()
{
    int tail = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), topo_order[++tail] = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--indeg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), G[v].push_back(u), indeg[v]++;
    toposort();
    for (int id = 1, u = topo_order[id]; id <= n; id++, u = topo_order[id])
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            atTail[edges[i].to] = max(atTail[edges[i].to], atTail[u] + 1);
    for (int id = n, u = topo_order[id]; id >= 1; id--, u = topo_order[id])
        for (int i = 0, siz = G[u].size(); i < siz; i++)
            atBegin[G[u][i]] = max(atBegin[G[u][i]], atBegin[u] + 1);
    for (int i = 1; i <= n; i++)
        ms.insert(atBegin[i]);
    int ans1 = 0, ans2 = n;
    for (int idx = 1; idx <= n; idx++)
    {
        int pivot = topo_order[idx];
        ms.erase(ms.find(atBegin[pivot]));
        // delete the potential edges;
        for (int i = 0, siz = G[pivot].size(); i < siz; i++)
            ms.erase(ms.find(atBegin[pivot] + atTail[G[pivot][i]] + 1));
        if (*ms.rbegin() < ans2)
            ans2 = *ms.rbegin(), ans1 = pivot;
        for (int i = head[pivot]; i != -1; i = edges[i].nxt)
            ms.insert(atTail[pivot] + atBegin[edges[i].to] + 1);
        ms.insert(atTail[pivot]);
    }
    printf("%d %d", ans1, ans2);
    return 0;
}