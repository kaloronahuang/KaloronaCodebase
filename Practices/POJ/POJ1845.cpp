// POJ1845.cpp
#include <iostream>
#define ll long long
using namespace std;
const int p = 9901;
ll a, b;
ll quickpow(ll base, ll tim, ll mod)
{
    ll ans = 1;
    for (; tim; tim >>= 1)
        if (tim & 1)
            base = base * ans % mod, ans = ans * ans % mod;
        else
            ans = ans * ans % mod;
    return ans;
}
ll sum(ll pc, ll c)
{
    if (c == 1)
        return (pc + 1) % p;
    if (c & 1)
        return (1 + quickpow(pc, (c + 1) >> 1, p)) * sum(pc, (c - 1) >> 1) % p;
    else
        return (1 + quickpow(pc, c >> 1, p)) * sum(pc, (c >> 1) - 1) % p;
}

int main()
{
    cin >> a >> b;
    return 0;
}