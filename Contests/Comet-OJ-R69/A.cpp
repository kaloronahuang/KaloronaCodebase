// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 1e9 + 7;

ll n;

int quick_pow(ll base, ll nt)
{
    int ans = 1, bas = base % mod, tim = nt % (mod - 1);
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
    scanf("%lld", &n);
    if (n <= 4)
        printf("%lld\n", n);
    else
    {
        ll m = floor(n / 3);
        if (n % 3 == 0)
            printf("%lld\n", quick_pow(3, m));
        else if (n % 3 == 1)
            printf("%lld\n", 4LL * quick_pow(3, m - 1) % mod);
        else
            printf("%lld\n", 2LL * quick_pow(3, m) % mod);
    }
    return 0;
}