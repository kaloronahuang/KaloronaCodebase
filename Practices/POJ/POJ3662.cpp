// POJ3662.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define pr pair<ll, ll>
using namespace std;
const ll MX_N = 1010;
ll head[MX_N], current = 0, n, p, k;
ll t1, t2, t3, dist[MX_N];
bool vis[MX_N], flag;
struct edge
{
    ll to, weight, nxt;
} edges[10200 << 1];
void addpath(ll src, ll dst, ll weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}
bool check(ll m)
{
    deque<pr> q;
    memset(vis, false, sizeof(vis)), memset(dist, 0x3f, sizeof(dist));
    q.push_back(make_pair(0, 1));
    dist[1] = 0;
    while (!q.empty())
    {
        pr pt = q.front();
        q.pop_front();
        ll u = pt.second, val = pt.first;
        if (u == n)
            return dist[u] <= k;
        if (vis[u])
            continue;
        vis[u] = true;
        for (ll i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > val + ((edges[i].weight > m) ? 1 : 0))
            {
                dist[edges[i].to] = val + ((edges[i].weight > m) ? 1 : 0);
                if (edges[i].weight > m)
                    q.push_back(make_pair(dist[edges[i].to], edges[i].to));
                else
                    q.push_front(make_pair(dist[edges[i].to], edges[i].to));
            }
    }
    flag = true;
    return false;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld%lld%lld", &n, &p, &k);
    ll tot = 0;
    for (ll i = 0; i < p; i++)
        scanf("%lld%lld%lld", &t1, &t2, &t3), addpath(t1, t2, t3), addpath(t2, t1, t3), tot += t3;
    ll l = 0, r = tot;
    while (l <= r && !flag)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    if (flag)
        printf("%d", -1);
    else
        printf("%lld", l);
    return 0;
}