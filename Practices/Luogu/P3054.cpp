// P3054.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200, upper = 1e6 + 200;

struct node
{
    ll r, rmod;
    bool operator<(const node &nd) const { return r < nd.r || (r == nd.r && rmod < nd.rmod); }
} nodes[MAX_N];

ll n, l, c, spd[MAX_N], mx_spd, h, tree[upper + 200];

inline ll lowbit(ll x) { return x & (-x); }

ll query(ll x)
{
    ll ans = 0;
    for (; x >= 1; x -= x & -x)
        ans += tree[x];
    return ans;
}

void update(ll x)
{
    for (; x <= upper; x += x & -x)
        tree[x]++;
}

int main()
{
    //freopen("testdata (2).in", "r", stdin);
    scanf("%lld%lld%lld", &n, &l, &c);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &spd[i]), mx_spd = max(mx_spd, spd[i]);
    for (int i = 1; i <= n; i++)
        nodes[i].r = spd[i] * l / mx_spd, nodes[i].rmod = spd[i] * l % mx_spd;
    sort(nodes + 1, nodes + 1 + n);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += (i - 1) * nodes[i].r - h - (query(upper) - query(nodes[i].rmod));
        h += nodes[i].r;
        if (nodes[i].rmod)
            update(nodes[i].rmod);
    }
    printf("%lld", ans);
    return 0;
}