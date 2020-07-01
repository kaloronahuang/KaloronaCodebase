// ARC090E.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int MAX_N = 1e5 + 200, MAX_E = 2e5 + 200, mod = 1e9 + 7;

int n, m, start_pos, end_pos, xi[MAX_E], yi[MAX_E], wi[MAX_E], head[MAX_N], current;
int dp[2][MAX_N], deg[MAX_N];
ll dist[2][MAX_N];
bool vis[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortestPath(int src, int id)
{
    memset(dist[id], 0x3f, sizeof(dist[id]));
    memset(vis, false, sizeof(vis));
    priority_queue<pli> pq;
    pq.push(make_pair(0, src)), dist[id][src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[id][edges[i].to] > dist[id][u] + edges[i].weight)
            {
                dist[id][edges[i].to] = dist[id][u] + edges[i].weight;
                pq.push(make_pair(-dist[id][edges[i].to], edges[i].to));
            }
    }
}

void build(int src, int id)
{
    for (int i = 1; i <= n; i++)
        G[i].clear(), deg[i] = 0;
    for (int i = 1; i <= m; i++)
        for (int rd = 0; rd < 2; rd++)
        {
            swap(xi[i], yi[i]);
            if (dist[id][xi[i]] + wi[i] == dist[id][yi[i]])
                G[xi[i]].push_back(yi[i]), deg[yi[i]]++;
        }
    queue<int> q;
    q.push(src), dp[id][src] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : G[u])
        {
            dp[id][v] = (0LL + dp[id][v] + dp[id][u]) % mod;
            if (--deg[v] == 0)
                q.push(v);
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &start_pos, &end_pos);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &xi[i], &yi[i], &wi[i]), addpath(xi[i], yi[i], wi[i]), addpath(yi[i], xi[i], wi[i]);
    shortestPath(start_pos, 0), build(start_pos, 0);
    shortestPath(end_pos, 1), build(end_pos, 1);
    int ans = 1LL * dp[0][end_pos] * dp[0][end_pos] % mod;
    for (int i = 1; i <= n; i++)
        if (dist[0][i] == dist[1][i] && dist[0][i] + dist[1][i] == dist[0][end_pos])
            ans = (0LL + ans + mod - 1LL * dp[0][i] * dp[0][i] % mod * dp[1][i] % mod * dp[1][i] % mod) % mod;
    for (int u = 1; u <= n; u++)
        if ((dist[0][u] << 1) < dist[0][end_pos])
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if ((dist[1][edges[i].to] << 1) < dist[0][end_pos] && dist[0][u] + edges[i].weight + dist[1][edges[i].to] == dist[0][end_pos])
                    ans = (0LL + ans + mod - 1LL * dp[0][u] * dp[0][u] % mod * dp[1][edges[i].to] % mod * dp[1][edges[i].to] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}