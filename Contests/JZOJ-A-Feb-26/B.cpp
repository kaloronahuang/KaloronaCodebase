/// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 100400, MAX_M = 1e5 + 2000;
int head[MAX_N], current, dfn[MAX_N], low[MAX_N], tot, st[MAX_N], hd, aff[MAX_N];
int totp, n, m, tmpx, tmpy, tmpz, ufs[MAX_N], dist[MAX_N];
bool inst[MAX_N];
struct edge
{
    int to, nxt, weight, from;
    bool operator<(const edge &e) const { return weight > e.weight; }
} edges[MAX_M << 1];
int find(int x) { return (ufs[x] == x) ? x : ufs[x] = find(ufs[x]); }
void unite(int x, int y)
{
    if (find(x) != find(y))
        ufs[find(x)] = find(y);
}
int addpath(int u, int v, int weight)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].from = u;
    edges[current].weight = weight, head[u] = current++;
    return current - 1;
}
void tarjan(int u)
{
    inst[u] = true, st[++hd] = u;
    dfn[u] = ++tot, low[u] = dfn[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int j;
        totp++;
        do
        {
            j = st[hd], aff[j] = totp;
            inst[j] = false;
        } while (st[hd--] != u);
    }
}
int main()
{
    while (scanf("%d%d", &n, &m) && n != 0 && m != 0)
    {
        memset(dist, 0x3f, sizeof(dist));
        memset(st, 0, sizeof(st)), memset(dfn, 0, sizeof(dfn)), hd = 0;
        for (int i = 1; i <= 2 * n; i++)
            ufs[i] = i;
        memset(head, -1, sizeof(head)), memset(aff, 0, sizeof(aff));
        totp = n, current = 0, tot = 0;
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx + 1, tmpy + 1, tmpz);
        tarjan(1);
        for (int i = 1; i <= n; i++)
            for (int e = head[i]; e != -1; e = edges[e].nxt)
                if (aff[i] != aff[edges[e].to])
                    dist[aff[edges[e].to]] = min(dist[aff[edges[e].to]], edges[e].weight);
        long long ans = 0;
        for (int i = n + 1; i <= totp; i++)
            if (aff[1] != i)
                ans += dist[i];
        printf("%lld\n", ans);
    }
    return 0;
}