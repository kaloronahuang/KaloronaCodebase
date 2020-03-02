// P4123.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_E = 8600;

int n, m, head[MAX_N], current, seq[MAX_N], dep[MAX_N];
set<int> cuts;

struct edge
{
    int to, nxt, weight, org_weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = edges[current].org_weight = weight, head[src] = current++;
}

bool bfs(int start_pos, int end_pos)
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

bool compare(const int &a, const int &b) { return (dep[a] ? dep[a] : 0x3f3f3f3f) < (dep[b] ? dep[b] : 0x3f3f3f3f); }

int dfs(int u, int flow, int end_pos)
{
    if (u == end_pos)
        return flow;
    int flow_tot = 0;
    for (int i = head[u]; i != -1 && flow; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight), end_pos))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                flow -= di, flow_tot += di;
            }
    if (flow_tot == 0)
        dep[u] = 0;
    return flow_tot;
}

void solve(int l, int r)
{
    if (l >= r)
        return;
    int acc = 0;
    while (bfs(seq[l], seq[r]))
        acc += dfs(seq[l], 0x3f3f3f3f, seq[r]);
    cuts.insert(acc), sort(seq + l, seq + r + 1, compare);
    int mid = 0;
    for (int i = l; i <= r; i++)
        if (dep[seq[i]] == 0)
        {
            mid = i;
            break;
        }
    for (int i = 0; i < current; i++)
        edges[i].weight = edges[i].org_weight;
    solve(l, mid - 1), solve(mid, r);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1; i <= n; i++)
        seq[i] = i;
    solve(1, n), printf("%d\n", int(cuts.size()));
    return 0;
}