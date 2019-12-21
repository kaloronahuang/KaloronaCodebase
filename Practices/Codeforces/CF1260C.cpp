// CF1260C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int T;
ll r, b, k;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld%lld", &r, &b, &k);
        ll d = gcd(r, b);
        r /= d, b /= d;
        if (r > b)
            swap(r, b);
        if ((k - 1) * r + 1 < b)
            puts("REBEL");
        else
            puts("OBEY");
    }
    return 0;
}