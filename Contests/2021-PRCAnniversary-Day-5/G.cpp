// G.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, c;

int main()
{
    scanf("%d%d", &c, &n);
    n /= c;
    if (n == 0)
        puts("-1");
    else
    {
        ll ans = 1LL * c * c;
        for (int i = n; i >= 1; i--)
            if (__gcd(i, n) == 1)
            {
                ans = 1LL * ans * i * n;
                break;
            }
        printf("%lld\n", ans);
    }
    return 0;
}