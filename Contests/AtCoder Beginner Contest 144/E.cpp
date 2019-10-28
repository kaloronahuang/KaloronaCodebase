// E.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200;

ll n, k, ci[MAX_N], di[MAX_N], tmp[MAX_N];

bool check(ll mid)
{
    for (ll i = 1; i <= n; i++)
        tmp[i] = mid / di[i];
    sort(tmp + 1, tmp + 1 + n);
    ll ans = 0;
    for (ll i = n; i >= 1; i--)
        ans += max(0LL, ci[i] - tmp[i]);
    return ans <= k;
}

int main()
{
    scanf("%lld%lld", &n, &k);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &ci[i]);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &di[i]);
    ll l = 0, r = 1e12, ans = 0;
    sort(ci + 1, ci + 1 + n), sort(di + 1, di + 1 + n);
    while (l <= r)
    {
        ll mid = (l + r) >> 1LL;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}