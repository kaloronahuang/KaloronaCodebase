// remapping.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200;

typedef long long ll;

ll n, weights[MAX_N];
int bin[MAX_N], mod, func[MAX_N], ptot, g[MAX_N], primes[MAX_N], tot;
bool vis[MAX_N];

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

int fpow(ll bas, ll tim)
{
    bas %= mod, tim %= (mod - 1);
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

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    /*
    for (int i = 1; i < MAX_N; i++)
        func[i] = 1;
    for (int i = 2; i < MAX_N; i++)
        if (!vis[i])
        {
            func[i] = 2;
            for (int j = (i << 1); j < MAX_N; j += i)
                vis[j] = true, func[j] = 1LL * func[j / i] * func[i] % mod;
        }
    for (int i = 1; i < MAX_N; i++)
        func[i] = (0LL + func[i] + func[i - 1]) % mod;
    */
}

int main()
{
    // fileIO("remapping");
    scanf("%lld%d", &n, &mod), sieve();
    cerr << tot << endl;
    printf("%d\n", func[n]);
    return 0;
}