// LOJ6714.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e6 + 200, mod = 998244353;

typedef long long ll;

ll n;
int f[MAX_N];
unordered_map<ll, int> mp;

int solve(ll x)
{
    if (x < MAX_N)
        return f[x];
    if (mp.count(x))
        return mp[x];
    int ret = 1;
    for (ll i = 2, gx; i <= x; i = gx + 1)
    {
        gx = (x / (x / i));
        ret = (0LL + ret + 1LL * (gx - i + 1) * solve(x / i) % mod) % mod;
    }
    return mp[x] = ret;
}

int main()
{
    scanf("%lld", &n);
    for (int i = f[1] = 1; i < MAX_N; i++)
        for (int j = i + i; j < MAX_N; j += i)
            f[j] = (0LL + f[j] + f[i]) % mod;
    for (int i = 1; i < MAX_N; i++)
        f[i] = (0LL + f[i] + f[i - 1]) % mod;
    printf("%d\n", solve(n));
    return 0;
}