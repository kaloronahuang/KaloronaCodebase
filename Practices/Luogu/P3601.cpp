// P3601.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 100, mod = 666623333;

ll l, r, ans, A[MAX_N], B[MAX_N], primes[MAX_N], ptot;
bool vis[MAX_N];

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++ptot] = i;
        for (int j = 1; j <= ptot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main()
{
    sieve(), scanf("%lld%lld", &l, &r);
    for (ll i = l; i <= r; i++)
        A[i - l] = i, B[i - l] = i;
    for (int i = 1; i <= ptot && 1LL * primes[i] * primes[i] <= r; i++)
    {
        ll p = primes[i];
        for (ll x = (p - l % p) % p; x <= r - l; x += p)
        {
            A[x] /= p, A[x] *= (p - 1);
            while (B[x] % p == 0)
                B[x] /= p;
        }
    }
    for (int i = 0; i <= r - l; i++)
    {
        // judge the biggest the prime factor;
        if (B[i] > 1)
            A[i] /= B[i], A[i] = 1LL * A[i] * (B[i] - 1);
        ans = (ans + i + l - A[i]) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}