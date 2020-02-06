// CF1295D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T;
ll a, m;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld", &a, &m);
        // \varphi(\lfloor \frac{m}{gcd(m, a)} \rfloor);
        ll d = gcd(a, m), x = m / d, ans = x;
        for (int i = 2; 1LL * i * i <= x; i++)
            if (x % i == 0)
            {
                ans = ans / i * (i - 1);
                while (x % i == 0)
                    x /= i;
            }
        if (x > 1)
            ans = ans / x * (x - 1);
        printf("%lld\n", ans);
    }
    return 0;
}