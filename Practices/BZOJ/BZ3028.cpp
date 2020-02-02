// BZ3028.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 510, mod = 10007;

char str[MAX_N];

int quick_pow(int bas, int tim)
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

int main()
{
    scanf("%s", str + 1);
    int n = 0;
    for (int i = 1; str[i] != '\0'; i++)
        n = ((n << 3) % mod + (n << 1) % mod + str[i] - '0') % mod;
    printf("%lld\n", 1LL * (n + 2) * (n + 1) % mod * n % mod * quick_pow(6, mod - 2) % mod);
    return 0;
}