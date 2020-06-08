// CF900D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 14, mod = 1e9 + 7;

int x, y;

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

int main()
{
    scanf("%d%d", &x, &y);
    if (y % x != 0)
        puts("0"), exit(0);
    y /= x;
    int acc = y;
    vector<int> primes;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            primes.push_back(i);
            while (acc % i == 0)
                acc /= i;
        }
    if (acc > 1)
        primes.push_back(acc);
    int n = primes.size(), ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
    {
        int prod = 1;
        for (int i = 0; i < n; i++)
            if (stat & (1 << i))
                prod *= primes[i];
        ans = (0LL + ans + mod + ((__builtin_popcount(stat) & 1) ? -1 : 1) * fpow(2, y / prod - 1) % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}