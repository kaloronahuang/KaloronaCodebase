// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX_N = 3e5 + 2000;
ll xi[MAX_N], yi[MAX_N], n, m;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

signed main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &xi[i]);
    for (ll i = 1; i <= m; i++)
        scanf("%lld", &yi[i]);
    sort(xi + 1, xi + 1 + n);
    ll d = xi[2] - xi[1];
    for (ll i = 3; i <= n; i++)
        d = gcd(d, xi[i] - xi[i - 1]);
    for (ll i = 1; i <= m; i++)
        if (d % yi[i] == 0)
            printf("YES\n%lld %lld", xi[1], i), exit(0);
    puts("NO");
    return 0;
}