// P1829.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e7 + 100, mod = 20101009;
ll n, m, mu[MAX_N], musum[MAX_N], prime[MAX_N], tot;
bool vis[MAX_N];
ll g(ll a, ll b) { return (((a * (a + 1)) / 2) % mod) * (((b * (b + 1)) / 2) % mod) % mod; }
ll sum(ll a, ll b)
{
    ll ans = 0;
    for (ll x = 1, y = 0; x <= a; x = y + 1)
    {
        y = min(a / (a / x), b / (b / x));
        ans = (ans + (musum[y] - musum[x - 1] + mod) % mod * g(a / x, b / x) % mod) % mod;
    }
    return ans;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    if (n > m)
        swap(n, m);
    mu[1] = 1;
    for (ll i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for (ll j = 1; j <= tot && i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            else
                mu[i * prime[j]] = -mu[i];
        }
    }
    for (ll i = 1; i < MAX_N; i++)
        musum[i] = (musum[i - 1] + (mu[i] + mod) % mod * (i * i % mod) % mod) % mod;
    ll ans = 0;
    for (ll x = 1, y = 0; x <= n; x = y + 1)
    {
        y = min(n / (n / x), m / (m / x));
        ans = (ans + (y - x + 1) * (y + x) / 2 % mod * sum(n / x, m / x) % mod) % mod;
    }
    printf("%lld", ans);
    return 0;
}