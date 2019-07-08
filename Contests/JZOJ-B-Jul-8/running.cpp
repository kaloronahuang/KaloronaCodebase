// running.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 60, MAX_DOM = 1e7 + 200;

ll n, m, arr[MAX_N], phi[MAX_DOM], prime[MAX_DOM], tot, ans;
unordered_map<ll, ll> ump;
bool vis[MAX_DOM];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll varphi(ll num)
{
    if (num < MAX_DOM)
        return phi[num];
    if (ump.count(num))
        return ump[num];
    ll ans = (num * (num + 1)) >> 1;

    for (ll d = 2, gx; d <= num; d = gx + 1)
    {
        gx = num / (num / d);
        ans -= (gx - d + 1) * varphi(num / d);
    }
    return ump[num] = ans;
}

void sieve()
{
    phi[1] = 1;
    for (ll i = 2; i < MAX_DOM; i++)
    {
        if (!vis[i])
            prime[++tot] = i, phi[i] = i - 1;
        for (ll j = 1; j <= tot && i * prime[j] < MAX_DOM; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 2; i < MAX_DOM; i++)
        phi[i] += phi[i - 1];
}

void solve(int factor)
{
    for (int i = 1; i <= m; i++)
        if (factor % gcd(arr[i], n) == 0)
        {
            ans += varphi(n / factor) - varphi(n / factor - 1);
            break;
        }
}

int main()
{
    /*
    freopen("running.in", "r", stdin);
    freopen("running.out", "w", stdout);
    */
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &arr[i]);
    sieve();
    for (int i = 1; i * i <= n; i++)
        if (n % i == 0)
        {
            solve(i);
            if (n / i != i)
                solve(n / i);
        }
    printf("%lld", n - ans);
    return 0;
}