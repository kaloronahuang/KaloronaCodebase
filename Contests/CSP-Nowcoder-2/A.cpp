// A.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 4e5 + 200;

ll n, m, q, ai[MAX_N];

int main()
{
    ll ans = 0;
    multiset<ll> ms;
    scanf("%lld%lld%lld", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), ms.insert(ai[i]), ans += ai[i];
    printf("%lld\n", max(*ms.rbegin(), (ll)(double(ans + m - 1) / double(m))));
    while (q--)
    {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        ans -= ai[x], ms.erase(ms.find(ai[x]));
        ms.insert(ai[x] = y), ans += ai[x];
        printf("%lld\n", max(*ms.rbegin(), (ll)(double(ans + m - 1) / double(m))));
    }
    return 0;
}