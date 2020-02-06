// P5171.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f(ll a, ll b, ll c, ll n)
{
    if (a == 0)
        return (b / c) * (n + 1);
    if (n == 0)
        return (b / c);
    if (max(a, b) >= c)
        return (f(a % c, b % c, c, n) + (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1));
    else
    {
        ll M = (a * n + b) / c;
        return (n * M - f(c, c - b - 1, a, M - 1));
    }
}

int main()
{
    ll a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    printf("%lld\n", f(a, c % a, b, c / a) + (c / a) + 1);
    return 0;
}