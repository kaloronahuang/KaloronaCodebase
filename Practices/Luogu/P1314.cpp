// P1314.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5e5 + 200;

int li[MAX_N], ri[MAX_N], n, m;
ll wi[MAX_N], vi[MAX_N], prefix_1[MAX_N], prefix_2[MAX_N], S;

ll check(ll mid)
{
    memset(prefix_1, 0, sizeof(prefix_1)), memset(prefix_2, 0, sizeof(prefix_2));
    for (int i = 1; i <= n; i++)
    {
        if (wi[i] >= mid)
            prefix_1[i] = 1, prefix_2[i] = vi[i];
        prefix_1[i] += prefix_1[i - 1], prefix_2[i] += prefix_2[i - 1];
    }
    ll Y = 0;
    for (int i = 1; i <= m; i++)
        Y += (prefix_1[ri[i]] - prefix_1[li[i] - 1]) * (prefix_2[ri[i]] - prefix_2[li[i] - 1]);
    return Y;
}

int main()
{
    scanf("%d%d%lld", &n, &m, &S);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &wi[i], &vi[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &li[i], &ri[i]);
    ll l = 0, r = 1e18, ans = r;
    while (l <= r)
    {
        ll mid = (l + r) >> 1, val = check(mid);
        if (val > S)
            l = mid + 1;
        else
            r = mid - 1;
        ans = min(ans, llabs(S - val));
    }
    printf("%lld", ans);
    return 0;
}