// P5023.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = 1e9 + 7;

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m)
        swap(n, m);
    if (n == 1)
        printf("%d", quick_pow(2, m));
    else if (n == 2)
        // decending sequence order makes it 3 options;
        printf("%lld", 4LL * quick_pow(3, m - 1) % mod);
    else if (n == 3)
        // What the fuck.
        printf("%lld", 112LL * quick_pow(3, m - 3) % mod);
    else
    {
        if (n == m)
            printf("%lld", (83LL * quick_pow(8, n) % mod + 5LL * quick_pow(2, n + 7) % mod) * quick_pow(384, mod - 2) % mod);
        else
            printf("%lld", (83LL * quick_pow(8, n) % mod + quick_pow(2, n + 8) % mod) % mod * quick_pow(128, mod - 2) % mod * quick_pow(3, m - n - 1) % mod);
    }

    return 0;
}