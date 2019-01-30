// HDU-2138.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, ans, tmp;
ll quick_pow(ll base, ll tim, ll p)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % p;
        base = base * base % p;
    }
    return tmp;
}
int main()
{
    scanf("%lld", &n);
    while (n--)
    {
        scanf("%lld", &tmp);
    }
    return 0;
}