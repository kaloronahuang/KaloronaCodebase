// POJ1639.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_N = 400, INF = 0x3f3f3f3f;

int n, m, ptot, S, mem[MAX_N], dist[MAX_N][MAX_N], ans, d[MAX_N], idx[MAX_N];
bool connected[MAX_N][MAX_N];

map<string, int> mp;

struct edge
{
    int src, to, weight;
    bool operator<(const edge &e) const { return weight < e.weight; }
} org[MAX_N], f[MAX_N];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void unite(int x, int y) { mem[find(x)] = find(y); }

void dfs(int u, int fa)
{
    for (int v = 2; v <= n; v++)
        if (v != fa && connected[u][v])
        {
            if (f[v].weight == -1)
                if (f[u].weight > dist[u][v])
                    f[v] = f[u];
                else
                    f[v].src = u, f[v].to = v, f[v].weight = dist[u][v];
            dfs(v, u);
        }
}

int main()
{
    memset(dist, 0x3f, sizeof(dist)), memset(d, 0x3f, sizeof(d));
    cin >> m;
    mp["Park"] = ptot = 1;
    for (int i = 0; i < MAX_N; i++)
        mem[i] = i;
    for (int i = 1, weight; i <= m; i++)
    {
        string src, dst;
        cin >> src >> dst >> weight;
        if (mp.count(src) == 0)
            mp[src] = ++ptot;
        if (mp.count(dst) == 0)
            mp[dst] = ++ptot;
        org[i].src = mp[src], org[i].to = mp[dst], org[i].weight = weight;
        dist[mp[src]][mp[dst]] = dist[mp[dst]][mp[src]] = min(dist[mp[src]][mp[dst]], weight);
    }
    cin >> S, n = ptot;
    sort(org + 1, org + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        if (org[i].src == 1 || org[i].to == 1)
            continue;
        int rtx = find(org[i].src), rty = find(org[i].to);
        if (rtx != rty)
        {
            unite(rtx, rty);
            connected[org[i].src][org[i].to] = connected[org[i].to][org[i].src] = true;
            ans += org[i].weight;
        }
    }
    // connect the id 1;
    for (int i = 2; i <= n; i++)
        if (dist[1][i] != INF && d[find(i)] > dist[1][i])
            d[find(i)] = dist[1][idx[find(i)] = i];
    for (int i = 1; i <= n; i++)
        if (d[i] != INF)
        {
            S--;
            connected[1][idx[i]] = connected[idx[i]][1] = true;
            ans += dist[1][idx[i]];
        }
    while (S--)
    {
        memset(f, -1, sizeof(f));
        f[1].weight = -INF;
        for (int i = 2; i <= n; i++)
            if (connected[1][i])
                f[i].weight = -INF;
        dfs(1, -1);
        int dst = 0, w = -INF;
        for (int i = 2; i <= n; i++)
            if (w < f[i].weight - dist[1][i])
                w = f[i].weight - dist[1][dst = i];
        if (w <= 0)
            break;
        connected[1][dst] = connected[dst][1] = true;
        connected[f[dst].src][f[dst].to] = connected[f[dst].to][f[dst].src] = false;
        ans -= w;
    }
    printf("Total miles driven: %d\n", ans);
    return 0;
}