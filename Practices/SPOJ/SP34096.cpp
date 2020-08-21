// SP34096.cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAX_N = 1e6 + 200;

ull T, idx[2][MAX_N], block, gtot, tot, g[MAX_N], weights[MAX_N], f[MAX_N], primes[MAX_N], n, kidx;
bool vis[MAX_N];

struct locator
{
    ull &operator[](const ull &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

void eularSieve()
{
    for (ull i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (ull j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void generateMin25()
{
    memset(g, 0, sizeof(ull) * (gtot + 5));
    gtot = 0, block = sqrt(n);
    for (ull i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        weights[++gtot] = n / i, loc[weights[gtot]] = gtot;
        g[gtot] = weights[gtot] - 1;
    }
    for (ull i = 1; i <= tot; i++)
        for (ull j = 1; j <= gtot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
            g[j] -= g[loc[weights[j] / primes[i]]] - (i - 1);
    for (ull i = 1; i <= gtot; i++)
        f[i] = 1LL * g[i] * (kidx + 1);
}

ull solve(ull upper, ull nid)
{
    if (upper <= primes[nid] || upper <= 1)
        return 0;
    ull ret = f[loc[upper]] - 1LL * nid * (kidx + 1);
    for (ull i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
        for (ull eid = 1, acc = primes[i]; 1LL * acc * primes[i] <= upper; eid++, acc *= primes[i])
            ret += solve(upper / acc, i) * (1 + eid * kidx) + (1 + (eid + 1) * kidx);
    return ret;
}

int main()
{
    eularSieve(), scanf("%d", &T);
    while (T--)
    {
        scanf("%llu%llu", &n, &kidx);
        generateMin25(), printf("%llu\n", solve(n, 0) + 1);
    }
    return 0;
}