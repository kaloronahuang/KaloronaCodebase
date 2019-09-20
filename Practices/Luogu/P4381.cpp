// BZ1791.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX_N = 3e6 + 200;

int head[MAX_N], n, deg[MAX_N], current, org[MAX_N], ccnt;
ll chain_dist[MAX_N], dist[MAX_N], dp[MAX_N], ans, q[MAX_N], chain[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), deg[u]--;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (deg[edges[i].to] > 1)
            {
                deg[edges[i].to]--;
                dp[org[u]] = max(dp[org[u]], dist[u] + dist[edges[i].to] + edges[i].weight);
                dist[edges[i].to] = max(dist[edges[i].to], dist[u] + edges[i].weight);
                if (deg[edges[i].to] == 1)
                    q.push(edges[i].to);
            }
    }
}

void dfs(int u, int fat, int og)
{
    org[u] = og;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!org[edges[i].to])
            dfs(edges[i].to, u, og);
}

void solve(int id, int blk)
{
    int m = 0;
    ll pt = id;
    bool flag = false;
    do
    {
        flag = false, chain[++m] = dist[pt];
        deg[pt] = 1;
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            if (deg[edges[i].to] > 1)
            {
                flag = true, pt = edges[i].to;
                chain_dist[m + 1] = chain_dist[m] + edges[i].weight;
            }
    } while (flag);
    if (m == 2)
    {
        // 2-node-loop;
        ll mx_len = 0;
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            if (edges[i].to == id)
                mx_len = max(mx_len, edges[i].weight);
        dp[blk] = max(dp[blk], dist[id] + dist[pt] + mx_len);
        return;
    }
    for (int i = head[pt]; i != -1; i = edges[i].nxt)
        if (edges[i].to == id)
        {
            chain_dist[m + 1] = chain_dist[m] + edges[i].weight;
            break;
        }
    for (int i = 1; i <= m; i++)
        chain[i + m] = chain[i], chain_dist[i + m] = chain_dist[m + 1] + chain_dist[i];
    int head = 1, tail = 1;
    q[1] = 1;
    for (int i = 2; i <= 2 * m; i++)
    {
        while (head <= tail && i - q[head] >= m)
            head++;
        dp[blk] = max(dp[blk], chain[q[head]] + chain[i] + max(chain_dist[i] - chain_dist[q[head]], chain_dist[m + 1] - (chain_dist[i] - chain_dist[q[head]])));
        while (head <= tail && chain[i] - chain_dist[i] >= chain[q[tail]] - chain_dist[q[tail]])
            tail--;
        q[++tail] = i;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int u = 1, v, w; u <= n; u++)
        scanf("%d%d", &v, &w), addpath(u, v, w), addpath(v, u, w), deg[u]++, deg[v]++;
    // done the preprocess;
    for (int i = 1; i <= n; i++)
        if (!org[i])
            dfs(i, 0, ++ccnt);
    toposort();
    // get the loop done;
    for (int i = 1; i <= n; i++)
        if (!vis[org[i]] && deg[i] > 1)
        {
            solve(i, org[i]);
            vis[org[i]] = true, ans += dp[org[i]];
        }
    printf("%lld", ans);
    return 0;
}