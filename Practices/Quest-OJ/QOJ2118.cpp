// QOJ2118.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, tot = 1;
ll ans;

struct seg
{
    int l, r;
} org[MAX_N];

void solve(int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt = mid;
    ll tmp = 0;
    for (int i = l; i <= min(mid - 1, r); i++)
        if (1LL * (org[mid].r - org[i].l) * (org[i].r - org[mid].l) > tmp)
            tmp = 1LL * (org[mid].r - org[i].l) * (org[i].r - org[mid].l), gpt = i;
    ans = max(ans, tmp);
    solve(l, gpt, LB, mid - 1), solve(gpt, r, mid + 1, RB);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &org[i].l, &org[i].r);
    sort(org + 1, org + 1 + n, [](const seg &a, const seg &b) { return a.l < b.l || (a.l == b.l && a.r > b.r); });
    for (int i = 2; i <= n; i++)
    {
        if (org[i].r <= org[tot].r)
            ans = max(ans, 1LL * (org[tot].r - org[tot].l) * (org[i].r - org[i].l));
        else
            org[++tot] = org[i];
    }
    solve(1, tot, 1, tot), printf("%lld\n", ans);
    return 0;
}