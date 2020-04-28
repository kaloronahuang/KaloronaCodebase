// POJ2409.cpp
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

int n, c;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    while (scanf("%d%d", &c, &n) != EOF && (n || c))
    {
        // rotation;
        ll ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ll d = gcd(n, i), pans = 1;
            while (d--)
                pans *= c;
            ans += pans;
        }
        if (n & 1)
        {
            ll pans = n;
            for (int i = 1; i <= (n >> 1) + 1; i++)
                pans *= c;
            ans += pans;  
        }
        else
        {
            ll pans = (n >> 1);
            for (int i = 1; i <= (n >> 1); i++)
                pans *= c;
            ans += pans;
            pans = (n >> 1);
            for (int i = 1; i <= (n >> 1) + 1; i++)
                pans *= c;
            ans += pans;
        }
        printf("%lld\n", ans / (2 * n));
    }
    return 0;
}