// POJ2417.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>
#define ll long long
using namespace std;
ll a, b, p;
ll quick_power(ll base, ll tim)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % p;
        base = base * base % p;
        tim >>= 1;
    }
    return tmp;
}
map<ll, ll> hashTable;
ll bsgs()
{
    if (a % p == 0)
        return -1;
    ll m = sqrt(p);
    hashTable.clear();
    for (int x = 1, j = 0; j < m; j++, x = x * a % p)
        hashTable[x * b % p] = j;
    ll q = quick_power(a, p - 1 - m), acc = 1;
    for (ll i = m;; i += m)
    {
    }
    return -1;
}
int main()
{
    while (~scanf("%lld%lld%lld", &a, &b, &p))
    {
        ll res = bsgs();
        if (res == -1)
            printf("no solution\n");
        else
            printf("%lld\n", res);
    }
    return 0;
}