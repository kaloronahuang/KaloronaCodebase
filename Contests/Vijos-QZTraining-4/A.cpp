// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, T;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        for (ll i = n >> 1, j = (n + 1) >> 1; i >= 1 && j <= n; i--, j++)
            if (gcd(i, j) == 1)
            {
                printf("%lld\n", i * j / gcd(i, j));
                break;
            }
    }
    return 0;
}