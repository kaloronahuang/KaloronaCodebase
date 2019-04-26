// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1010000, mod = 1000000007;
ll prob[MAX_N], n, f[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%lld", &n);
    ll dom = 1;
    for (int i = 1; i <= n; i++)
    {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        prob[i] = a * quick_pow(b, mod - 2) % mod;
        dom = dom * prob[i] % mod;
    }
    dom = quick_pow(dom, mod - 2);
    ll answer = 0, preprob = 1;
    for (int i = 1; i <= n; i++)
    {
        ll f = preprob * (1 - prob[i] + mod) % mod;
        preprob = preprob * prob[i] % mod;
        answer = (answer + f * i % mod * dom % mod) % mod;
    }
    answer = (answer + n) % mod;
    printf("%lld", answer);
    return 0;
}