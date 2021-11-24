// G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int T, n, m, dist[MAX_N * MAX_N][MAX_N * MAX_N], tot, gans = 0x7fffffff, pans;
vector<int> bikes, parks;
char mp[MAX_N][MAX_N];
bool vis[MAX_N];

int getId(int x, int y) { return (x - 1) * m + y; }

bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

void dfs(int u)
{
    if (u == bikes.size())
        return (void)(gans = min(gans, pans));
    for (int i = 0; i < parks.size(); i++)
        if (!vis[i] && dist[bikes[u]][parks[i]] != 0x3f3f3f3f)
            pans += dist[bikes[u]][parks[i]], vis[i] = true, dfs(u + 1), vis[i] = false, pans -= dist[bikes[u]][parks[i]];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        gans = 0x7fffffff;
        scanf("%d%d", &n, &m), tot = n * m;
        for (int i = 1; i <= n; i++)
            scanf("%s", mp[i] + 1);
        memset(dist, 0x3f, sizeof(dist));
        bikes.clear(), parks.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (mp[i][j] != 'Q' && mp[i][j] != 'H')
                {
                    if (mp[i][j] == 'C')
                        bikes.push_back(getId(i, j));
                    if (mp[i][j] == 'P')
                        parks.push_back(getId(i, j));
                }
        for (int i = 1; i <= tot; i++)
            dist[i][i] = 0;
        for (int ux = 1; ux <= n; ux++)
            for (int uy = 1; uy <= m; uy++)
                if (mp[ux][uy] != 'Q' && mp[ux][uy] != 'H')
                {
                    int id = getId(ux, uy);
                    queue<pair<int, int>> qp;
                    qp.push(make_pair(ux, uy)), dist[id][id] = 0;
                    while (!qp.empty())
                    {
                        int cx = qp.front().first, cy = qp.front().second;
                        qp.pop();
                        for (int d = 0; d < 4; d++)
                        {
                            int dstx = cx + dx[d], dsty = cy + dy[d];
                            if (check(dstx, dsty) && mp[dstx][dsty] != 'Q' && mp[dstx][dsty] != 'H' && dist[id][getId(dstx, dsty)] > dist[id][getId(cx, cy)] + 1)
                                dist[id][getId(dstx, dsty)] = dist[id][getId(cx, cy)] + 1, qp.push(make_pair(dstx, dsty));
                        }
                    }
                }
        dfs(0), printf("%d\n", gans);
    }
    return 0;
}