// bag3.out
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 510;

int flightMatrix[MAX_N][MAX_N], n, m, rp[MAX_N], ans = 0x3f3f3f3f;

struct flight
{
    int src, dst, sttime, edtime;

    bool operator<(const flight &fl) const { return sttime < fl.sttime || (sttime == fl.sttime && edtime < fl.edtime); }
} flights[MAX_N];
int aff[MAX_N];
bool vis[MAX_N];

void dfs(int u, int acc)
{
    if (acc >= ans)
        return;
    if (u == n + 1)
    {
        // validate;
        for (int idx = 1; idx <= acc; idx++)
            for (int i = 1, last = 0; i <= n; i++)
                if (aff[i] == idx)
                    if (last == 0)
                        last = i;
                    else if (flights[last].edtime + flightMatrix[flights[last].dst][flights[i].src] + rp[flights[i].src] < flights[i].sttime)
                        continue;
                    else
                        return;
        ans = min(ans, acc);
        return;
    }
    for (int i = 1; i <= acc; i++)
    {
        aff[u] = i;
        dfs(u + 1, acc);
        aff[u] = 0;
    }
    aff[u] = acc + 1, dfs(u + 1, acc + 1), aff[u] = 0;
}

int main()
{
    freopen("bag3.in", "r", stdin);
    freopen("bag3.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &rp[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &flightMatrix[i][j]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &flights[i].src, &flights[i].dst, &flights[i].sttime);
        flights[i].edtime = flightMatrix[flights[i].src][flights[i].dst] + rp[flights[i].dst];
    }
    sort(flights + 1, flights + 1 + m);
    dfs(1, 0);
    printf("%d", ans);
    return 0;
}