// ARC066D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;

ll n;
map<ll, int> mp;

int solve(ll x)
{
    if (mp.count(x) > 0)
        return mp[x];
    else
        return mp[x] = (0LL + solve(x >> 1) + solve((x - 1) >> 1) + solve((x - 2) >> 1)) % mod;
}

int main()
{
    mp[0] = 1, mp[1] = 2;
    scanf("%lld", &n), printf("%d\n", solve(n));
    return 0;
}