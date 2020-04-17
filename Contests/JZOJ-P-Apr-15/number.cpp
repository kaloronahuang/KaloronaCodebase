// number.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, d, mu[MAX_N], primes[MAX_N], tot, psiz[MAX_N];
bool vis[MAX_N];
multiset<int> pos;
ll ans;

void fileIO()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
}

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

int main()
{
    // fileIO();
    n = read(), d = read();
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
    // printf("%.6lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    // answer the queries;
    while (n--)
    {
        int opt = read(), x = read();
        if (x % d != 0)
        {
            printf("%lld\n", ans);
            continue;
        }
        x /= d;
        if (opt == 1)
        {
            pos.insert(x);
            for (int i = 1; 1LL * i * i <= x; i++)
                if (x % i == 0)
                {
                    ans += mu[i] * psiz[i], psiz[i]++;
                    if (x / i != i)
                        ans += mu[x / i] * psiz[x / i], psiz[x / i]++;
                }
        }
        else
        {
            if (pos.find(x) == pos.end())
            {
                printf("%lld\n", ans);
                continue;
            }
            pos.erase(pos.find(x));
            for (int i = 1; 1LL * i * i <= x; i++)
                if (x % i == 0)
                {
                    psiz[i]--, ans -= mu[i] * psiz[i];
                    if (x / i != i)
                        psiz[x / i]--, ans -= mu[x / i] * psiz[x / i];
                }
        }
        printf("%lld\n", ans);
    }
    // printf("%.6lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}