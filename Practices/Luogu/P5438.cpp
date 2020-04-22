// P5438.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200;

typedef long long ll;

int primes[MAX_N], tot, mu[MAX_N], pre[MAX_N], pre2[MAX_N];
bool vis[MAX_N];

void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true, mu[i * primes[j]] = -mu[i];
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < MAX_N; i++)
        pre[i] = pre[i - 1] + mu[i], pre2[i] = pre2[i - 1] + abs(mu[i]);
}

ll solve(ll x)
{
    if (x < MAX_N)
        return x - pre2[x];
    ll ans = 0, block = sqrt(x);
    for (ll i = 2, gx; i <= block; i = gx + 1)
    {
        gx = min(block, ll(sqrt(x / (x / (i * i)))));
        ans -= x / (i * i) * (pre[gx] - pre[i - 1]);
    }
    return ans;
}

int main()
{
    ll l, r;
    scanf("%lld%lld", &l, &r), sieve();
    ll ans = solve(r) - solve(l - 1), last_lft = l - 1;
    for (ll c = 2; c * c <= r; c++)
    {
        ll lft = (l - 1) / (c * c), rig = min(last_lft, r / (c * c));
        if (rig > lft)
            ans -= ((rig - lft) - (solve(rig) - solve(lft)));
        last_lft = lft;
    }
    printf("%lld\n", ans);
    return 0;
}