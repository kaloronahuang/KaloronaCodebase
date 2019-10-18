// P2607.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e6 + 200;

int head[MAX_N], current, n, val[MAX_N], deg[MAX_N];
ll dp[MAX_N][2], dp2[MAX_N][2];
bool tag[MAX_N], vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0)
            tag[i] = true;
}

vector<int> order;

void goOrder(int u, int fa)
{
    vis[u] = true;
    order.push_back(u);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (tag[edges[i].to] && edges[i].to != fa && vis[edges[i].to] == false)
            goOrder(edges[i].to, u);
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && tag[edges[i].to] == false)
        {
            dfs(edges[i].to, u);
            dp[u][0] += max(dp[edges[i].to][0], dp[edges[i].to][1]);
            dp[u][1] += dp[edges[i].to][0];
        }
    dp[u][1] += val[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d%d", &val[i], &tmp), addpath(i, tmp), addpath(tmp, i), deg[tmp]++;
    toposort();
    for (int i = 1; i <= n; i++)
        if (tag[i])
            dfs(i, 0);
    // merge the chain;
    ll ans = 0;
    // force the head to make it;
    bool flag = false;
    for (int i = 1; i <= n; i++)
        if (tag[i] && !vis[i])
        {
            order.clear();
            goOrder(i, 0);
            int loop_size = order.size();
            ll gans = 0;
            if (flag)
                memset(dp2, 0, sizeof(dp2));
            flag = true;
            dp2[0][1] = dp[order[0]][1];
            for (int i = 1; i < loop_size; i++)
            {
                dp2[i][0] = max(dp2[i - 1][0], dp2[i - 1][1]) + dp[order[i]][0];
                if (i != 1 && i != loop_size - 1)
                    dp2[i][1] = dp2[i - 1][0] + dp[order[i]][1];
            }
            gans = max(gans, max(dp2[loop_size - 1][0], dp2[loop_size - 1][1]));
            memset(dp2, 0, sizeof(dp2));
            dp2[0][0] = dp[order[0]][0];
            for (int i = 1; i < loop_size; i++)
            {
                dp2[i][0] = max(dp2[i - 1][0], dp2[i - 1][1]) + dp[order[i]][0];
                dp2[i][1] = dp2[i - 1][0] + dp[order[i]][1];
            }
            gans = max(gans, max(dp2[loop_size - 1][0], dp2[loop_size - 1][1]));
            ans += gans;
        }
    printf("%lld", ans);
    return 0;
}