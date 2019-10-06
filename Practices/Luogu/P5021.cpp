// P5021.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 50500;

int head[MAX_N], current, n, prod[MAX_N], m;
ll dist[MAX_N];
vector<ll> sons[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int getPairs(int u, int mid, int tot, ll limit)
{
    int ret = 0;
    for (int r = tot - 1, l = 0; r >= 1; r--)
    {
        r -= (r == mid);
        while (l < r && sons[u][l] + sons[u][r] < limit)
            l++;
        l += (l == mid);
        if (l >= r)
            break;
        ret++, l++;
    }
    return ret;
}

void dfs(int u, int fa, ll limit)
{
    dist[u] = prod[u] = 0;
    sons[u].clear();
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u, limit);
            dist[edges[i].to] += edges[i].weight;
            if (dist[edges[i].to] >= limit)
                prod[u]++;
            else
                sons[u].push_back(dist[edges[i].to]);
        }
    int siz = sons[u].size();
    sort(sons[u].begin(), sons[u].end());
    int res = 0;
    for (int r = siz - 1, l = 0; r >= 1; r--)
    {
        while (l < r && sons[u][l] + sons[u][r] < limit)
            l++;
        if (l >= r)
            break;
        res++, l++;
    }
    prod[u] += res;
    if ((res << 1) == siz)
        return;
    int l = 0, r = siz - 1, ret;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (getPairs(u, mid, siz, limit) == res)
            ret = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    dist[u] = sons[u][ret];
}

bool check(ll limit)
{
    int lane_tot = 0;
    dfs(1, 0, limit);
    for (int i = 1; i <= n; i++)
        lane_tot += prod[i];
    return lane_tot >= m;
}

int main()
{
    memset(head, -1, sizeof(head));
    ll l = 0, r = 0, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), r += w;
    r /= 1LL * m;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%lld", ans);
    return 0;
}