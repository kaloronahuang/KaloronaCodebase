// 51Nod1847.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, MAX_K = 66;

int n, k, primes[MAX_N], tot, idx[2][MAX_N], weights[MAX_N], ftot;
signed phi[MAX_N], sphi[MAX_N], g[3][MAX_N], Snd[MAX_K][MAX_K], pre[MAX_N];
bool vis[MAX_N];

struct locator
{
    int &operator[](const int &rhs) { return 1LL * rhs * rhs <= n ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

signed fpow(signed bas, int tim)
{
    signed ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret *= bas;
        bas *= bas;
        tim >>= 1;
    }
    return ret;
}

void preprocess()
{
    phi[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, phi[i] = i - 1, pre[tot] = pre[tot - 1] + fpow(primes[tot], k);
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
        }
    }
    for (int i = 1; i < MAX_N; i++)
        sphi[i] = sphi[i - 1] + phi[i];
    Snd[0][0] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= i; j++)
            Snd[i][j] = Snd[i - 1][j] * j + Snd[i - 1][j - 1];
}

unordered_map<int, signed> ump;

signed sieve_phi(int upper)
{
    if (upper < MAX_N)
        return sphi[upper];
    if (ump.find(upper) != ump.end())
        return ump[upper];
    signed ret = (1LL * upper * (upper + 1) / 2);
    for (int i = 2, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        ret -= sieve_phi(upper / i) * (gx - i + 1);
    }
    return ump[upper] = ret;
}

signed prefixPow(int n, int idx = k)
{
    signed ret = 0;
    for (int i = 0; i <= idx; i++)
    {
        signed pans = 1;
        bool flag = false;
        for (int j = 0; j <= i; j++)
            if (!flag && (n + 1 - j) % (i + 1) == 0)
                pans *= (n + 1 - j) / (i + 1), flag = true;
            else
                pans *= (n + 1 - j);
        ret += pans * Snd[idx][i];
    }
    return ret;
}

void min25_initialize()
{
    for (int i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        weights[++ftot] = n / i;
        g[0][ftot] = prefixPow(weights[ftot]) - 1, g[1][ftot] = weights[ftot] - 1;
        loc[n / i] = ftot;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ftot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
        {
            int id = loc[weights[j] / primes[i]];
            g[0][j] -= fpow(primes[i], k) * (g[0][id] - pre[i - 1]);
            g[1][j] -= (g[1][id] - i + 1);
            g[2][j] += (g[0][id] - pre[i - 1]);
        }
}

int main()
{
    scanf("%d%d", &n, &k), preprocess();
    min25_initialize();
    signed ans = 0;
    for (int i = 1, gx; i <= n; i = gx + 1)
        gx = n / (n / i), ans += (2 * sieve_phi(n / i) - 1) * (g[2][loc[gx]] + g[1][loc[gx]] - (i > 1 ? (g[2][loc[i - 1]] + g[1][loc[i - 1]]) : 0));
    printf("%u\n", ans);
    return 0;
}