// CF1103D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, MAX_M = 12;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
ll k, ai[MAX_N], ei[MAX_N], d, f[13][1 << MAX_M];
vector<ll> primes;
map<ll, vector<int> /**/> mp;
bool valid[1 << MAX_M];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), d = gcd(ai[i], d);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ei[i]);
    for (ll i = 2; 1LL * i * i <= d; i++)
        if (d % i == 0)
        {
            primes.push_back(i);
            while (d % i == 0)
                d /= i;
        }
    if (d > 1)
        primes.push_back(d);
    m = primes.size();
    for (int i = 1; i <= n; i++)
    {
        ll tmp = 1;
        for (int j = 0; j < m; j++)
            while (ai[i] % primes[j] == 0)
                ai[i] /= primes[j], tmp *= primes[j];
        mp[tmp].push_back(ei[i]);
    }
    memset(f, 0x3f, sizeof(f)), f[0][0] = 0;
    ll ans = INF;
    for (auto &curt : mp)
    {
        ll u = curt.first;
        sort(curt.second.begin(), curt.second.end());
        if (1LL * curt.second.size() > m)
            curt.second.resize(k);
        for (int stat = 0; stat < (1 << m); stat++)
        {
            ll tmp = u, acc = 1;
            for (int j = 0; j < m; j++)
                if (stat & (1 << j))
                    while (tmp % primes[j] == 0)
                        tmp /= primes[j], acc *= primes[j];
            valid[stat] = (acc <= k);
        }
        for (auto cost : curt.second)
        {
            bool vis = false;
            for (int i = m - 1; i >= 0; i--)
                for (int stat = 0; stat < (1 << m); stat++)
                    if (f[i][stat] < INF)
                        for (int substat = (stat + 1) | stat; substat < (1 << m); substat = (substat + 1) | stat)
                            if (valid[substat ^ stat] && f[i + 1][substat] > f[i][stat] + cost)
                                vis = true, f[i + 1][substat] = f[i][stat] + cost;
            // no where to relax;
            if (!vis)
                break;
        }
    }
    for (int i = 0; i <= m; i++)
        if (f[i][(1 << m) - 1] < INF)
            ans = min(ans, 1LL * f[i][(1 << m) - 1] * i);
    if (ans == INF)
        puts("-1");
    else
        printf("%lld\n", ans);
    return 0;
}