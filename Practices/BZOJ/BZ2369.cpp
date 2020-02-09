// BZ2369.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

struct seg
{
    int l, r;
    bool operator<(const seg &rhs) const { return l < rhs.l || (l == rhs.l && r > rhs.r); }
} segs[MAX_N], org[MAX_N];

int n, stot;
ll ans, dp[MAX_N];

ll calc(int i, int j) { return 1LL * (segs[i].r - segs[j].l) * (segs[j].r - segs[i].l); }

void solve(int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt;
    ll tmp, max_val = 0;
    for (int i = l; i <= min(mid - 1, r); i++)
    {
        ll tmp = calc(i, mid);
        if (tmp > max_val)
            gpt = i, max_val = tmp;
    }
    dp[mid] = max_val, ans = max(ans, max_val);
    if (max_val > 0)
        solve(l, gpt, LB, mid - 1), solve(gpt, r, mid + 1, RB);
    else
        solve(l, mid, LB, mid - 1), solve(mid + 1, r, mid + 1, RB);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &org[i].l, &org[i].r);
    sort(org + 1, org + 1 + n), segs[stot = 1] = org[1];
    for (int i = 2; i <= n; i++)
    {
        if (org[i].r <= segs[stot].r)
            ans = max(ans, 1LL * (segs[stot].r - segs[stot].l) * (org[i].r - org[i].l));
        else
            segs[++stot] = org[i];
    }
    solve(1, stot, 1, stot);
    printf("%lld\n", ans);
    return 0;
}