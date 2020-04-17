// POJ2154.cpp
#include <iostream>
#include <cstdio>

using namespace std;

int T, n, mod;

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int phi(int x)
{
    int ret = x;
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            ret -= ret / i;
            while (x % i == 0)
                x /= i;
        }
    if (x != 1)
        ret -= ret / x;
    return ret % mod;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &mod);
        int ans = 0;
        for (int i = 1; 1LL * i * i <= n; i++)
            if (n % i == 0)
            {
                ans = (0LL + ans + 1LL * fpow(n, i - 1) * phi(n / i) % mod) % mod;
                if (1LL * i * i != n)
                    ans = (0LL + ans + 1LL * fpow(n, (n / i) - 1) * phi(i) % mod) % mod;
            }
        printf("%d\n", ans);
    }
    return 0;
}