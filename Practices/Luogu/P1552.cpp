// P1552.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
const int MAX_N = 100100;
struct node
{
    int lson, rson;
    ll dist;
} nodes[MAX_N];
ll n, m, li[MAX_N], ci[MAX_N], master, ans = -2e9;
ll sum[MAX_N], siz[MAX_N], pt[MAX_N];
vector<int> G[MAX_N];
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (ci[x] < ci[y])
        swap(x, y);
    nodes[x].rson = merge(nodes[x].rson, y);
    if (nodes[nodes[x].lson].dist < nodes[nodes[x].rson].dist)
        swap(nodes[x].lson, nodes[x].rson);
    nodes[x].dist = nodes[nodes[x].rson].dist + 1;
    return x;   
}
void dfs(int u)
{
    sum[u] = ci[u], siz[u] = 1, pt[u] = u;
    int siz_ = G[u].size();
    for (int i = 0; i < siz_; i++)
    {
        int to = G[u][i];
        dfs(to);
        sum[u] += sum[to], siz[u] += siz[to];
        pt[u] = merge(pt[u], pt[to]);
    }
    while (sum[u] > m && siz[u])
    {
        sum[u] -= ci[pt[u]];
        pt[u] = merge(nodes[pt[u]].rson, nodes[pt[u]].lson);
        siz[u]--;
    }
    ans = max(ans, li[u] * siz[u]);
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        ll fa;
        scanf("%lld%lld%lld", &fa, &ci[i], &li[i]);
        if (fa == 0)
            master = i;
        else
            G[fa].push_back(i);
    }
    dfs(master);
    printf("%lld", ans);
    return 0;
}