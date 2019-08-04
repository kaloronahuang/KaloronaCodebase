// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, mod = 998244353;

int id, T, c, ci[MAX_N], m, func[12000], primes[12000];
bool isPrime[10001];

inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

inline int quick_pow(int bas, int tim, int modulo)
{
    int ans = 1;
    bas %= modulo;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % modulo;
        bas = 1LL * bas * bas % modulo;
        tim >>= 1;
    }
    return ans;
}

inline int sieve(int n)
{
    int ans = 2;
    for (register int i = 2; i <= n - 1; i++)
    {
        if (!isPrime[i])
            func[i] = quick_pow(i, m, n);
        for (register int j = 1; j <= n - 1; j++)
        {
            if (i * primes[j] > n)
                break;
            func[i * primes[j]] = func[i] * func[primes[j]] % n;
            if (i % primes[j] == 0)
                break;
        }
        ans += func[i] == i;
    }
    return ans;
}

int main()
{
    /*
    freopen("division.in", "r", stdin);
    freopen("division.out", "w", stdout);
    */

    int tot = 0;
    for (register int i = 2; i <= 10000; i++)
    {
        if (!isPrime[i])
            primes[++tot] = i;
        for (register int j = 1; j <= tot; j++)
        {
            if (i * primes[j] > 10000)
                break;
            isPrime[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }

    id = read(), T = read();
    while (T--)
    {
        int ans = 1;
        c = read(), m = read();
        for (register int i = 1; i <= c; i++)
            ci[i] = read(), ans = 1LL * ans * sieve(ci[i]) % mod;
        printf("%d\n", ans);
    }
    return 0;
} // B.cpp