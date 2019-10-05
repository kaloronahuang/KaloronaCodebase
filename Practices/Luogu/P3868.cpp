// P3868.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 20;

ll ai[MAX_N], bi[MAX_N];
int n;

ll multiply(ll a, ll b, ll mod)
{
    ll ans = 0;
    for (; b != 0; b >>= 1, a = (a + a) % mod)
        if (b & 1)
            ans = (ans + a) % mod;
    return ans;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), t = x;
    x = y, y = t - a / b * y;
    return d;
}

ll crt()
{
    ll modulo = 1, sx, sy, ans = 0;
    for (int i = 1; i <= n; i++)
        modulo *= bi[i];
    for (int i = 1; i <= n; i++)
    {
        ll m = modulo / bi[i];
        exgcd(bi[i], m, sx, sy), sy = ((sy % bi[i]) + bi[i]) % bi[i];
        ans = (ans + multiply(sy, multiply(m, (ai[i] + modulo) % modulo, modulo), modulo) + modulo) % modulo;
    }
    while (ans < 0)
        ans += modulo;
    ans %= modulo;
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &bi[i]);
    printf("%lld", crt());
    return 0;
}