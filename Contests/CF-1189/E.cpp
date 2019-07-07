// E.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 4e5 + 2000;

ll n, mod, k, seq[MAX_N], ans;

unordered_map<ll, ll> ump;

int main()
{
    scanf("%lld%lld%lld", &n, &mod, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &seq[i]);
        ll res = (seq[i] * seq[i] % mod * seq[i] % mod * seq[i] % mod - k * seq[i] % mod + mod) % mod;
        ans += ump[res];
        ump[res]++;
    }
    printf("%lld", ans);
    return 0;
}