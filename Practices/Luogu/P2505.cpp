// P2505.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, m, head[MAX_N], current, dist[MAX_N], ui[MAX_N], vi[MAX_N], wi[MAX_N], ans[MAX_N], deg[MAX_N];
int coeff[2][MAX_N], order[MAX_N];
vector<int> G[MAX_N];
bool vis[MAX_N], ins[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pair<int, int> /**/> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &ui[i], &vi[i], &wi[i]), addpath(ui[i], vi[i], wi[i]);
    for (int start_pt = 1, ptot; start_pt <= n; start_pt++)
    {
        memset(coeff, 0, sizeof(coeff)), memset(ins, false, sizeof(ins));
        memset(deg, 0, sizeof(deg)), ptot = 0;
        for (int i = 1; i <= n; i++)
            G[i].clear();
        shortest_path(start_pt);
        for (int i = 1; i <= m; i++)
            if (dist[vi[i]] == dist[ui[i]] + wi[i])
                ins[i] = true, G[ui[i]].push_back(vi[i]), deg[vi[i]]++;
        queue<int> q;
        q.push(start_pt), coeff[0][start_pt] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop(), order[++ptot] = u;
            for (int i = 0, siz = G[u].size(); i < siz; i++)
            {
                if (--deg[G[u][i]] == 0)
                    q.push(G[u][i]);
                coeff[0][G[u][i]] = (0LL + coeff[0][u] + coeff[0][G[u][i]]) % mod;
            }
        }
        for (int u = ptot; u >= 1; u--)
        {
            coeff[1][order[u]]++;
            for (int i = 0, siz = G[order[u]].size(); i < siz; i++)
                coeff[1][order[u]] = (0LL + coeff[1][order[u]] + coeff[1][G[order[u]][i]]) % mod;
        }
        for (int i = 1; i <= m; i++)
            if (ins[i])
                ans[i] = (0LL + ans[i] + 1LL * coeff[0][ui[i]] * coeff[1][vi[i]] % mod) % mod;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}