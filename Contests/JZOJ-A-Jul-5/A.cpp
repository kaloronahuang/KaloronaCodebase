// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll INF = 0x3f3f3f3f3f3f3f3f, MAX_N = 1010, MAX_E = 5050;

ll n, m, k, ans = INF, fa[MAX_N], current_ans, siz[MAX_N], dat[MAX_N];

struct edge
{
    ll from, to, frequency;
    bool operator<(const edge& e) const { return frequency < e.frequency; }
} edges[MAX_E];

void ufs_initialize()
{
    for (ll i = 1; i <= n; i++)
        fa[i] = i, siz[i] = 1;
}

ll find(ll x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unite(ll x, ll y) 
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    if (siz[x] < siz[y])
        swap(x, y);
    current_ans -= dat[siz[x]] + dat[siz[y]];
    fa[y] = fa[x], siz[x] += siz[y];
    current_ans += dat[siz[x]];
}

signed main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &dat[i]);
    for (ll i = 1; i <= m; i++)
        scanf("%lld%lld%lld", &edges[i].from, &edges[i].to, &edges[i].frequency);
    sort(edges + 1, edges + 1 + m);
    for (ll lbound = 1, lower = edges[1].frequency; lbound <= m; lbound++, lower = edges[lbound].frequency)
    {
        ufs_initialize(), current_ans = dat[1] * n;
        for (ll rbound = lbound, upper = edges[rbound].frequency; rbound <= m; rbound++, upper = edges[rbound].frequency)
        {
            ll width = upper - lower;
            unite(edges[rbound].from, edges[rbound].to);
            if (current_ans >= k)
            {
                ans = min(ans, width);
                break;
            }
        }
    }
    if (ans == INF)
        puts("T_T");
    else
        printf("%lld", ans);
    return 0;
}