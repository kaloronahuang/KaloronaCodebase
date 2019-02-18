// POJ1845.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD = 9901;
ll A, B, p[20], c[20], tot;
void divide(ll num)
{
    for (ll i = 2; i * i <= num; i++)
        if (num % i == 0)
        {
            tot++;
            while (num % i == 0)
                c[tot]++, num /= i;
            p[tot] = i;
        }
    if (num > 1)
        p[++tot] = num, c[tot] = 1;
}
ll quick_power(ll base, ll tim, ll mod)
{
    base %= mod;
    ll ans = 1 % mod;
    while (tim)
    {
        if (tim & 1)
            ans = ans * base % mod;
        base = base * base % mod;
        tim >>= 1;
    }
    return ans;
}
int main()
{
    scanf("%lld%lld", &A, &B);
    divide(A);
    ll ans = 1;
    for (int i = 1; i <= tot; i++)
    {
        if ((p[i] - 1) % MOD == 0)
        {
            ans = (B * c[i] + 1) % MOD * ans % MOD;
            continue;
        }
        ll x = quick_power(p[i], B * c[i] + 1, MOD);
        x = (x - 1 + MOD) % MOD;
        ll bas = p[i] - 1;
        bas = quick_power(bas, MOD - 2, MOD);
        ans = ans * x % MOD * bas % MOD;
    }
    printf("%lld", ans);
    return 0;
}