// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 1e5 + 20000;
ll n, k, A, B, pos[MAX_N];

ll getNum(ll l, ll r)
{
    return lower_bound(pos + 1, pos + 1 + k, r + 1) - lower_bound(pos + 1, pos + 1 + k, l);
}

ll solve(ll l, ll r)
{
    ll mid = (l + r) >> 1, num = getNum(l, r);
    if (num == 0)
        return A;
    ll ans = num * (r - l + 1) * B;
    if (l != r)
        ans = min(ans, solve(l, mid) + solve(mid + 1, r));
    return ans;
}

int main()
{
    scanf("%lld%lld%lld%lld", &n, &k, &A, &B);
    for (ll i = 1; i <= k; i++)
        scanf("%lld", &pos[i]);
    sort(pos + 1, pos + 1 + k);
    printf("%lld", solve(1, (1 << n)));
    return 0;
}