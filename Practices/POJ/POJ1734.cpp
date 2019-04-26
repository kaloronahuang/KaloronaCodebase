// POJ1734.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
typedef long long ll;
using namespace std;

const ll MAX_N = 110, INF = 0x3f3f3f3f;
ll G[MAX_N][MAX_N], n, m, dist[MAX_N][MAX_N], tmpx, tmpy, tmpz;
ll pos[MAX_N][MAX_N];
vector<ll> path;

void addpath(ll x, ll y)
{
    if (pos[x][y] == 0)
        return;
    addpath(x, pos[x][y]);
    path.push_back(pos[x][y]);
    addpath(pos[x][y], y);
}

signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G[i][j] = INF;
    for (ll i = 1; i <= n; i++)
        G[i][i] = 0;
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &tmpx, &tmpy, &tmpz);
        G[tmpx][tmpy] = G[tmpy][tmpx] = min(G[tmpx][tmpy], tmpz);
    }

    memcpy(dist, G, sizeof(G));
    long long answer = INF;
    for (ll k = 1; k <= n; k++)
    {
        for (ll i = 1; i < k; i++)
            for (ll j = i + 1; j < k; j++)
                if (answer > dist[i][j] + G[j][k] + G[k][i])
                {
                    answer = dist[i][j] + G[j][k] + G[k][i];
                    path.clear();
                    path.push_back(i);
                    addpath(i, j);
                    path.push_back(j), path.push_back(k);
                }
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= n; j++)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pos[i][j] = k;
                }
    }
    if (answer == INF)
        puts("No solution."), exit(0);
    for (int i = 0, siz = path.size(); i < siz; i++)
        printf("%d ", path[i]);
    puts("");
    return 0;
}