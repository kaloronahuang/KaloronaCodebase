// P5022.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, m, deg[MAX_N], ST, ED;
vector<int> ans, now, G[MAX_N];

void dfs(int u, int fa)
{
    now.push_back(u);
    for (int i = 0, siz = G[u].size(); i < siz; i++)
    {
        if ((ST == u && ED == G[u][i]) || (ST == G[u][i] && ED == u) || fa == G[u][i])
            continue;
        dfs(G[u][i], u);
    }
}

bool compare()
{
    if (ans.empty())
        return true;
    for (int i = 0; i < n; i++)
        if (now[i] < ans[i])
            return true;
        else if (now[i] > ans[i])
            return false;
    return false;
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
        q.pop();
        for (int i = 0, siz = G[u].size(); i < siz; i++)
            if (--deg[G[u][i]] == 1)
                q.push(G[u][i]);
    }
}

int main()
{

    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), deg[u]++, deg[v]++, G[u].push_back(v), G[v].push_back(u);
    for (int i = 1; i <= n; i++)
        sort(G[i].begin(), G[i].end());
    if (m == n - 1)
    {
        dfs(1, 0);
        for (int i = 0, siz = now.size(); i < siz; i++)
            printf("%d ", now[i]);
        return 0;
    }
    else
    {
        toposort();
        for (int u = 1; u <= n; u++)
            for (int i = 0, siz = G[u].size(); i < siz; i++)
                if (u < G[u][i] && deg[u] > 1 && deg[G[u][i]] > 1)
                {
                    ST = u, ED = G[u][i];
                    now.clear();
                    dfs(1, 0);
                    if (compare())
                        swap(ans, now);
                }
        for (int i = 0, siz = ans.size(); i < siz; i++)
            printf("%d ", ans[i]);
    }

    return 0;
}