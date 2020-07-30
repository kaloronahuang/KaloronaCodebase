// triangle.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int MAX_N = 1e7 + 200, mod = 1e9 + 7;

ll n, m;
int primes[MAX_N], tot, mu[3][MAX_N], org_mu[MAX_N];
bool vis[MAX_N];
map<pii, int> ump;

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

const int inv2 = fpow(2, mod - 2), inv6 = fpow(6, mod - 2);

void sieve()
{
    mu[0][1] = 1, org_mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[0][i] = mod - 1, org_mu[i] = mod - 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[0][i * primes[j]] = 0, org_mu[i * primes[j]] = 0;
                break;
            }
            mu[0][i * primes[j]] = (mod - mu[0][i]) % mod, org_mu[i * primes[j]] = (mod - org_mu[i]) % mod;
        }
    }
    for (int i = 1; i < MAX_N; i++)
        for (int j = 0, acc = mu[0][i]; j < 3; j++, acc = 1LL * acc * i % mod)
            mu[j][i] = (0LL + mu[j][i - 1] + acc) % mod;
}

int calc(int idx, ll upper)
{
    upper %= mod;
    if (idx == 0)
        return upper;
    if (idx == 1)
        return 1LL * upper * (upper + 1) % mod * inv2 % mod;
    return 1LL * upper * (upper + 1) % mod * ((2LL * upper % mod + 1) % mod) % mod * inv6 % mod;
}

int sieve(int idx, ll upper)
{
    if (upper < MAX_N)
        return mu[idx][upper];
    if (ump.count(make_pair(idx, upper)))
        return ump[make_pair(idx, upper)];
    int ret = 1;
    for (ll i = 2, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        int coeff = (0LL + calc(idx, gx) + mod - calc(idx, i - 1)) % mod;
        ret = (0LL + ret + mod - 1LL * coeff * sieve(idx, upper / i) % mod) % mod;
    }
    return ump[make_pair(idx, upper)] = ret;
}

int main()
{
    /*
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    */
    scanf("%lld%lld", &n, &m), sieve();
    if (n > m)
        swap(n, m);
    for (int i = 0; i < 3; i++)
        sieve(i, n), sieve(i, m);
    int ans = 0;
    for (ll k = 1, gx; k <= n; k = gx + 1)
    {
        gx = min(n / (n / k), m / (m / k));
        int mu_coeff = (0LL + sieve(0, gx) + mod - sieve(0, k - 1)) % mod;
        ans = (0LL + ans + 4LL * (n % mod) % mod * (m % mod) % mod * ((n / k) % mod) % mod * ((m / k) % mod) % mod * mu_coeff % mod) % mod;
    }
    for (ll k = 1, gx; k <= n; k = gx + 1)
    {
        gx = min(n / (n / k), m / (m / k));
        int pans = 1LL * ((m / k) % mod) * (m % mod) % mod * calc(1, n / k) % mod;
        pans = (0LL + pans + 1LL * ((n / k) % mod) * (n % mod) % mod * calc(1, m / k) % mod) % mod;
        int mu_coeff = (0LL + sieve(1, gx) + mod - sieve(1, k - 1)) % mod;
        ans = (0LL + ans + mod - 4LL * mu_coeff % mod * pans % mod) % mod;
    }
    for (ll k = 1, gx; k <= n; k = gx + 1)
    {
        gx = min(n / (n / k), m / (m / k));
        int mu_coeff = (0LL + sieve(2, gx) + mod - sieve(2, k - 1)) % mod;
        ans = (0LL + ans + 4LL * mu_coeff % mod * calc(1, n / k) % mod * calc(1, m / k) % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}