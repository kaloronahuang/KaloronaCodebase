// P4777.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll multiply(ll a, ll b, ll mod)
{
    ll ans = 0;
    for (; b; a = (a + a) % mod, b >>= 1)
        if (b & 1)
            ans = (ans + a) % mod;
    return ans;
}

ll exgcd(ll &x, ll &y, ll a, ll b)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(x, y, b, a % b), tmp = x;
    x = y, y = tmp - (a / b) * y;
    return d;
}

const int MAX_N = 1e5 + 200;

ll n, bi[MAX_N], ai[MAX_N];

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &ai[i], &bi[i]);
    ll ans = bi[1], M = ai[1];
    for (int i = 2; i <= n; i++)
    {
        ll b = ((bi[i] - ans) % ai[i] + ai[i]) % ai[i], x, y;
        ll gcd = exgcd(x, y, M, ai[i]);
        x = multiply(x, b / gcd, ai[i]);
        ans += M * x;
        M *= ai[i] / gcd, ans = (ans + M) % M;
    }
    printf("%lld", ans);
    return 0;
}