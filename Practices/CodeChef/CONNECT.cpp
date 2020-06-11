// CONNECT.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 16, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0}, INF = 0x3f3f3f3f;

int n, m, threshold, idx[MAX_N * MAX_N], mat[MAX_N * MAX_N], cost[MAX_N * MAX_N];
int dp[1 << 7][MAX_N * MAX_N];
vector<int> G[MAX_N * MAX_N];
queue<int> q;
bool vis[MAX_N * MAX_N];

int getId(int x, int y)
{
    return (x - 1) * m + y;
}

unsigned int Rand()
{
    static unsigned int x = 19260817;
    x ^= (x << 5);
    x ^= (x >> 17);
    x ^= (x << 13);
    return x;
}

int check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

void spfa(int stat)
{
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int v : G[u])
            if (dp[stat][v] > dp[stat][u] + cost[v])
            {
                dp[stat][v] = dp[stat][u] + cost[v];
                if (!vis[v])
                    q.push(v), vis[v] = true;
            }
    }
}

int main()
{
    srand(time(NULL));
    scanf("%d%d%d", &n, &m, &threshold);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mat[getId(i, j)]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &cost[getId(i, j)]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mat[getId(i, j)] != -1)
                for (int d = 0; d < 4; d++)
                    if (check(i + dx[d], j + dy[d]) && mat[getId(i + dx[d], j + dy[d])] != -1)
                        G[getId(i, j)].push_back(getId(i + dx[d], j + dy[d]));
    int T = 600, res = INF;
    while (T--)
    {
        map<int, int> idsys;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (mat[getId(i, j)] != -1 && idsys.count(getId(i, j)) == 0)
                    idsys[getId(i, j)] = rand() % threshold;
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (mat[getId(i, j)] != -1)
                    dp[mat[getId(i, j)] == 0 ? 0 : (1 << idsys[mat[getId(i, j)]])][getId(i, j)] = cost[getId(i, j)];
        for (int stat = 0; stat < (1 << threshold); stat++)
        {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                {
                    int pt = getId(i, j);
                    if (mat[pt] == -1)
                        continue;
                    for (int sub = stat & (stat - 1); sub; sub = (sub - 1) & stat)
                        dp[stat][pt] = min(dp[stat][pt], dp[stat ^ sub][pt] + dp[sub][pt] - cost[pt]);
                    if (dp[stat][pt] <= res && !vis[pt])
                        q.push(pt), vis[pt] = true;
                }
            spfa(stat);
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                res = min(res, dp[(1 << threshold) - 1][getId(i, j)]);
    }
    printf("%d\n", res >= 1e9 ? -1 : res);
    return 0;
}