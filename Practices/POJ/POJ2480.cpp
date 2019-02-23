// POJ2480.cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#define ll long long
using namespace std;
map<ll, ll> prefix;
vector<ll> getFracted(ll x)
{
    vector<ll> res;
    for (ll i = 1; i * i <= x; i++)
        if (x % i == 0)
        {
            res.push_back(i);
            if (i != x / i)
                res.push_back(x / i);
        }
    return res;
}
ll phi(ll x)
{
    ll ans = x;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            ans -= ans / i;
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        ans -= ans / x;
    return ans;
}
int main()
{
    ll n;
    while (scanf("%lld", &n) != EOF)
    {
        ll ans = 0;
        vector<ll> container = getFracted(n);
        ll siz = container.size();
        for (int i = 0; i < siz; i++)
        {
            if (!prefix.count(n / container[i]))
                prefix[n / container[i]] = phi(n / container[i]);
            ll e = prefix[n / container[i]];
            ans += e * container[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}