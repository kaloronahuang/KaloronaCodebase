// P4562.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 2000, mod = 1e9 + 7;

int L, R, fac[MAX_N], inv[MAX_N], fac_inv[MAX_N], primes[MAX_N], tot;
bool tag[MAX_N];

int binomial(int n_, int m_) { return 1LL * fac[n_] * fac_inv[n_ - m_] % mod * fac_inv[m_] % mod; }

int main()
{
    scanf("%d%d", &L, &R);
    for (int i = fac[0] = 1; i <= R; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= R; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = fac_inv[0] = 1; i <= R; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    for (int i = L; i <= R; i++)
        if (!tag[i])
        {
            primes[++tot] = i;
            for (long long j = i << 1; j <= R; j += i)
                tag[j] = true;
        }
    int ans = 0;
    for (int i = tot; i <= R - L + 1; i++)
        ans = (0LL + ans + 1LL * binomial(i - 1, tot - 1) * fac[R - L + 1 - tot] % mod * fac[tot] % mod * i % mod) % mod;
    printf("%d\n", ans);
    return 0;
}