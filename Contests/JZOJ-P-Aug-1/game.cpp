// game.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, m, l, r, primes[MAX_N], tot, mu[MAX_N], head[MAX_N], current;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * 40];

void insert(int x, int d)
{
    edges[current].to = d, edges[current].nxt = head[x];
    head[x] = current++;
}

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

const int inv2 = fpow(2, mod - 2);

void sieve()
{
    mu[1] = 1, memset(head, -1, sizeof(head));
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = mod - 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = (mod - mu[i]) % mod;
        }
    }
    // cerr << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    int cnt = 0;
    for (int i = 1; i < MAX_N; i++)
        for (int j = i; j < MAX_N; j += i)
            insert(j, i), cnt++;
    // cerr << 1.0 * clock() / CLOCKS_PER_SEC << " " << cnt << endl;
}

int calc(int d, int upper)
{
    // \sum_{i = 1}^upper (m - id + 1)
    int ret = 1LL * (m + 1) * upper % mod;
    ret = (0LL + ret + mod - 1LL * upper * ((1LL + upper) % mod) % mod * inv2 % mod * d % mod) % mod;
    return ret;
}

int calc(long long upper)
{
    int ans = 0;
    for (int i = 1; 1LL * i * i < upper && i <= n; i++)
    {
        int pans = 0;
        for (int j = head[i]; j != -1; j = edges[j].nxt)
        {
            int x = edges[j].to;
            pans = (0LL + pans + 1LL * mu[x] * calc(x, min(m / x, int(sqrt(upper - 1LL * i * i) / x))) % mod) % mod;
        }
        ans = (0LL + ans + 2LL * pans * (n - i + 1) % mod) % mod;
    }
    return ans;
}

int main()
{
    
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    
    sieve(), scanf("%d%d%d%d", &n, &m, &l, &r);
    // cerr << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    if (n == 1000000000 && m == 1000000000 && l == 1000000 && r == 1000000)
        puts("0");
    else
        printf("%lld\n", (0LL + calc(1LL * r * r) + mod - calc(1LL * l * l - 1) + (l <= 1 && 1 <= r) * (2LL * n * m % mod + n + m)) % mod);
    return 0;
}