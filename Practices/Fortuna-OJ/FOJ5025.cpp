// FOJ5025.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;

const int MAX_N = 1e6 + 200;

ll n, weights[MAX_N];
int primes[MAX_N], tot, ptot, idx[2][MAX_N], block;
uint g[3][MAX_N], pre[3][MAX_N];
bool vis[MAX_N];

struct locator
{
    int &operator[](const ll &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

uint calc2(ll x)
{
    if (x & 1)
        return (x + 1) / 2 * x;
    return 1LL * x / 2 * (x + 1);
}

uint calc3(ll x)
{
    ll f[3] = {x, x + 1, 2 * x + 1};
    for (int i = 0; i < 3; i++)
        if (f[i] % 2 == 0)
        {
            f[i] /= 2;
            break;
        }
    for (int i = 0; i < 3; i++)
        if (f[i] % 3 == 0)
        {
            f[i] /= 3;
            break;
        }
    return uint(f[0]) * uint(f[1]) * uint(f[2]);
}

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
        {
            primes[++tot] = i;
            for (uint j = 0, acc = 1; j < 3; j++, acc *= i)
                pre[j][tot] = pre[j][tot - 1] + acc;
        }
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

uint solve(ll upper, int nid)
{
    if (upper < primes[nid] || upper <= 1)
        return 0;
    uint ret = 3 * (g[2][loc[upper]] - g[1][loc[upper]]) + g[0][loc[upper]];
    ret -= 3 * (pre[2][nid - 1] - pre[1][nid - 1]) + pre[0][nid - 1];
    for (int i = nid; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
    {
        uint e = 3, p = primes[i], p2 = p * p, p_1 = 1, unit = p2;
        for (ll acc = primes[i]; 1LL * acc * primes[i] <= upper; acc *= primes[i])
        {
            uint f = e * (p2 - p) + p_1;
            ret += f * solve(upper / acc, i + 1) + (e + 2) * (p2 - p) * unit + p_1 * primes[i];
            e += 2, p *= unit, p2 *= unit, p_1 *= primes[i];
        }
    }
    return ret;
}

int main()
{
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    scanf("%lld", &n), block = sqrt(n), sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        weights[++ptot] = n / i, loc[n / i] = ptot;
        g[0][ptot] = uint(weights[ptot]) - 1;
        g[1][ptot] = calc2(weights[ptot]) - 1;
        g[2][ptot] = calc3(weights[ptot]) - 1;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
            for (uint k = 0, acc = 1; k < 3; k++, acc *= primes[i])
                g[k][j] -= acc * (g[k][loc[weights[j] / primes[i]]] - pre[k][i - 1]);
    printf("%u\n", solve(n, 1) + 1);
    return 0;
}