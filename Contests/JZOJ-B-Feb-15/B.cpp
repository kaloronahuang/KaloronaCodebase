// B.cpp
// Complexity:
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>
using namespace std;
const int MAX_N = 10010, MAX_M = 50010;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, k, t, head[MAX_N], current, tmpx, tmpy, tmpz, mp[20];
ll dist[20][MAX_N], neomap[20][20], f[(1 << 17)][20];
bool vis[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 1];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}
int getOnBit(int num)
{
    int ans = 0;
    while (num)
        if (num & 1)
            ans++, num >>= 1;
        else
            num >>= 1;
    return ans;
}
void djisktra(int u)
{
    memset(vis, false, sizeof(vis));
    priority_queue<pr> q;
    int org = mp[u];
    q.push(make_pair(0, org)), dist[u][org] = 0;
    while (!q.empty())
    {
        int curt = q.top().second;
        q.pop();
        if (vis[curt])
            continue;
        vis[curt] = true;
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
        {
            int to = edges[i].to;
            if (dist[u][to] > dist[u][curt] + edges[i].weight)
                dist[u][to] = dist[u][curt] + edges[i].weight, q.push(make_pair(-dist[u][to], to));
        }
    }
}
int main()
{
    memset(dist, 0x3f, sizeof(dist)), memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &k, &t);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    for (int i = 0; i < k; i++)
        scanf("%d", &tmpx), mp[i] = tmpx;
    mp[k] = n, mp[k + 1] = 1;
    for (int i = 0; i <= k + 1; i++)
        djisktra(i);
    for (int i = 0; i <= k + 1; i++)
        for (int j = 0; j <= k + 1; j++)
            neomap[i][j] = dist[i][mp[j]];
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k; j++)
            f[(1 << i)][j] = neomap[k + 1][i];
    for (int stat = 1; stat < (1 << (k + 1)); stat++)
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
                if ((((stat >> i) & 1) == 1) && (((stat >> j) & 1) == 0))
                    f[stat | (1 << j)][j] = min(f[stat | (1 << j)][j], f[stat][i] + neomap[i][j]);
    ll ans1 = 0, ans2 = INF;
    for (int stat = 1; stat < (1 << (k + 1)); stat++)
    {
        if (getOnBit(stat) < ans1 || ((stat >> k) & 1) == 0)
            continue;
        ll tmp = INF;
        for (int i = 0; i <= k; i++)
            if (((stat >> i) & 1) == 1)
                tmp = min(tmp, f[stat][i] + neomap[i][k + 1]);
        if (tmp != INF && tmp <= t)
            ans2 = (ans1 < getOnBit(stat)) ? tmp : min(ans2, tmp), ans1 = getOnBit(stat);
    }
    printf("%lld %lld", ans1 - 1, ans2);
    return 0;
}