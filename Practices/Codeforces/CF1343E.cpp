// CF1343E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int T, n, m, node[3], dist[3][MAX_N];
ll prices[MAX_N];
vector<int> G[MAX_N];

void bfs(int idx)
{
    queue<int> q;
    q.push(node[idx]), dist[idx][node[idx]] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : G[u])
            if (dist[idx][v] == -1)
                dist[idx][v] = dist[idx][u] + 1, q.push(v);
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            G[i].clear();
        for (int i = 0; i < 3; i++)
        {
            scanf("%d", &node[i]);
            for (int j = 1; j <= n; j++)
                dist[i][j] = -1;
        }
        for (int i = 1; i <= m; i++)
            scanf("%lld", &prices[i]);
        for (int i = 1, u, v; i <= m; i++)
            scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
        sort(prices + 1, prices + 1 + m);
        for (int i = 1; i <= m; i++)
            prices[i] += prices[i - 1];
        for (int i = 0; i < 3; i++)
            bfs(i);
        ll ans = 0x3f3f3f3f3f3f3f3f;
        for (int i = 1; i <= n; i++)
        {
            int d1 = dist[0][i], d2 = dist[1][i], d3 = dist[2][i];
            if (d1 + d2 + d3 > m)
                continue;
            ans = min(ans, prices[d1 + d2 + d3] + (d2 == 0 ? 0 : prices[d2]));
        }
        printf("%lld\n", ans);
    }
    return 0;
}