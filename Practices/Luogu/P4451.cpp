// P4451.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

long long n;
char str[int(1e5) + 200];

int quick_pow(long long bas, long long tim)
{
    tim %= (mod - 1), bas %= mod;
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

int main()
{
    scanf("%s", str + 1);
    for (int i = 1; str[i] != '\0'; i++)
        n = (n * 10 + str[i] - '0') % (mod - 1);
    printf("%lld\n", (1LL * 485071604 * quick_pow(940286408, n - 1) % mod + 1LL * 514928404 * quick_pow(59713601, n - 1) % mod) % mod);
    return 0;
}