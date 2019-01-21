// B.cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
const int mod = 998244353, MAX_N = 1e6 + 200;
ll level[MAX_N], rev[MAX_N];
ll quick_power(ll base, ll tim)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % mod;
        base = base * base % mod;
        tim >>= 1;
    }
    return tmp;
}
int main()
{
    ll n, limit;
    scanf("%lld", &n);
    if (n % 4 == 2 || n % 4 == 3)
        printf("0"), exit(0);
    int m = n / 4;
    limit = 2 * m;
    level[0] = 1;
    for (int i = 1; i <= limit; i++)
        level[i] = level[i - 1] * i % mod;
    ll lr = rev[limit] = quick_power(level[limit], mod - 2);
    rev[0] = 1;
    for (int i = limit - 1; i > 0; i--)
        rev[i] = lr * (i + 1) % mod, lr = lr * (i + 1) % mod;
    ll ret = level[2 * m] * rev[m] % mod;
    printf("%d", ret);
    return 0;
}