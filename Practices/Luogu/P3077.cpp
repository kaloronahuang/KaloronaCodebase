// P3077.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 40010, MAX_R = 2001000;

ll dpl[MAX_N], dpr[MAX_N], val_lft[MAX_N], val_rig[MAX_N], n, m, r, ans = -0x3f3f3f3f3f3f3f3f;

struct edge
{
    int u, v;
    bool operator<(const edge &x) const { return u < x.u || (u == x.u && v < x.v); }
} edges[MAX_R << 1];

int main()
{
    scanf("%lld%lld%lld", &n, &m, &r);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &val_lft[i]), ans = max(ans, val_lft[i]);
    for (int i = 1; i <= m; i++)
        scanf("%lld", &val_rig[i]), ans = max(ans, val_rig[i]);
    for (int i = 1; i <= r; i++)
        scanf("%d%d", &edges[i].u, &edges[i].v);
    sort(edges + 1, edges + 1 + r);
    dpl[edges[1].u] = val_lft[edges[1].u] + val_rig[edges[1].v];
    dpr[edges[1].v] = dpl[edges[1].u];
    for (int i = 2; i <= r; i++)
        if (edges[i].u != edges[i - 1].u || edges[i].v != edges[i - 1].v)
        {
            // do the transfer;
            ll lf_dp = dpl[edges[i].u], rg_dp = dpr[edges[i].v];
            ll val_lf = val_lft[edges[i].u], val_rg = val_rig[edges[i].v];
            if (lf_dp == 0)
                dpr[edges[i].v] = max(dpr[edges[i].v], val_lf + val_rg);
            else
                dpr[edges[i].v] = max(dpr[edges[i].v], lf_dp + val_rg);
            if (rg_dp == 0)
                dpl[edges[i].u] = max(dpl[edges[i].u], val_lf + val_rg);
            else
                dpl[edges[i].u] = max(dpl[edges[i].u], rg_dp + val_lf);
        }
    for (int i = 1; i <= n; i++)
        ans = max(ans, dpl[i]);
    for (int i = 1; i <= m; i++)
        ans = max(ans, dpr[i]);
    printf("%lld", ans);
    return 0;
}