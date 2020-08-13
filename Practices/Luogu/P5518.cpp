// P5518.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, A, B, C, mod, primes[MAX_N], tot, mu[MAX_N], pmu[MAX_N], fac[MAX_N], fac_inv[MAX_N];
int func[3][MAX_N], phi[MAX_N];
bool vis[MAX_N];

int fpow(int bas, int tim)
{
    if (tim < 0)
        tim = (tim % (mod - 1) + (mod - 1)) % (mod - 1);
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
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    mu[1] = pmu[1] = phi[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = mod - 1, pmu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = pmu[i * primes[j]] = 0;
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            pmu[i * primes[j]] = -pmu[i];
            mu[i * primes[j]] = (0LL + mod - mu[i]) % mod;
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        phi[i] = (0LL + phi[i] + phi[i - 1]) % (mod - 1);
    fill(func[0], func[0] + 1 + MAX_N, 1), func[1][0] = func[2][0] = 1;
    for (int d = 1; d < MAX_N; d++)
        for (int acc = d; acc < MAX_N; acc += d)
            func[0][acc] = 1LL * func[0][acc] * fpow(d, pmu[acc / d]) % mod;
    for (int i = 1; i < MAX_N; i++)
    {
        func[1][i] = 1LL * func[1][i - 1] * fpow(func[0][i], 1LL * i * i % (mod - 1)) % mod;
        func[0][i] = 1LL * func[0][i - 1] * func[0][i] % mod;
        func[2][i] = 1LL * func[2][i - 1] * fpow(i, phi[i]) % mod;
    }
}

namespace Subtask1
{

    int handler()
    {
        int upper1 = 1LL * fpow(fac[A], B) * fpow(fac[B], A) % mod;
        int lower1 = 1;
        for (int T = 1, gx; T <= min(A, B); T = gx + 1)
        {
            gx = min(A / (A / T), B / (B / T));
            lower1 = 1LL * lower1 * fpow(1LL * func[0][gx] % mod * fpow(func[0][T - 1], mod - 2) % mod, 1LL * (A / T) * (B / T) % (mod - 1)) % mod;
        }
        int ret1 = fpow(1LL * upper1 * fpow(lower1, mod - 2) % mod, C), ret2 = 1;
        for (int T = 1, gx; T <= min(A, C); T = gx + 1)
        {
            gx = min(A / (A / T), C / (C / T));
            ret2 = 1LL * ret2 * fpow(1LL * func[0][gx] % mod * fpow(func[0][T - 1], mod - 2) % mod, 1LL * (A / T) * (C / T) % (mod - 1)) % mod;
        }
        return 1LL * ret1 * fpow(fpow(ret2, mod - 2), B) % mod;
    }

} // namespace Subtask1

namespace Subtask2
{

    int S(int upper) { return 1LL * upper * (upper + 1) / 2 % (mod - 1); }

    int handler()
    {
        int ret1 = 1;
        for (int i = 1; i <= A; i++)
            ret1 = 1LL * ret1 * fpow(i, 1LL * i * S(B) % (mod - 1) * S(C) % (mod - 1)) % mod;
        for (int i = 1; i <= B; i++)
            ret1 = 1LL * ret1 * fpow(i, 1LL * i * S(A) % (mod - 1) * S(C) % (mod - 1)) % mod;
        int ret2 = 1;
        for (int T = 1, gx; T <= min(A, B); T = gx + 1)
        {
            gx = min(A / (A / T), B / (B / T));
            ret2 = 1LL * ret2 * fpow(1LL * func[1][gx] % mod * fpow(func[1][T - 1], mod - 2) % mod, 1LL * S(A / T) * S(B / T) % (mod - 1)) % mod;
        }
        ret2 = fpow(ret2, S(C));
        int ret3 = 1;
        for (int T = 1, gx; T <= min(A, C); T = gx + 1)
        {
            gx = min(A / (A / T), C / (C / T));
            ret3 = 1LL * ret3 * fpow(1LL * func[1][gx] % mod * fpow(func[1][T - 1], mod - 2) % mod, 1LL * S(A / T) * S(C / T) % (mod - 1)) % mod;
        }
        ret3 = fpow(ret3, S(B));
        return 1LL * ret1 * fpow(ret2, mod - 2) % mod * fpow(ret3, mod - 2) % mod;
    }

} // namespace Subtask2

namespace Subtask3
{

    int handler()
    {
        int ret1 = 1, ret2 = 1, ret3 = 1, ret4 = 1;
        for (int T = 1, gx; T <= A; T = gx + 1)
        {
            gx = min(A / (A / T), min(B / (B / T), C / (C / T)));
            int pans = fpow(1LL * func[2][gx] * fpow(func[2][T - 1], mod - 2) % mod, 1LL * (A / T) * (B / T) % (mod - 1) * (C / T) % (mod - 1));
            pans = 1LL * pans * fpow(fac[A / T], 1LL * (0LL + phi[gx] + mod - 1 - phi[T - 1]) % (mod - 1) * (B / T) % (mod - 1) * (C / T) % (mod - 1)) % mod;
            ret1 = 1LL * ret1 * pans % mod;
        }
        for (int T = 1, gx; T <= B; T = gx + 1)
        {
            gx = min(A / (A / T), min(B / (B / T), C / (C / T)));
            int pans = fpow(1LL * func[2][gx] * fpow(func[2][T - 1], mod - 2) % mod, 1LL * (A / T) * (B / T) % (mod - 1) * (C / T) % (mod - 1));
            pans = 1LL * pans * fpow(fac[B / T], 1LL * (0LL + phi[gx] + mod - 1 - phi[T - 1]) % (mod - 1) * (A / T) % (mod - 1) * (C / T) % (mod - 1)) % mod;
            ret2 = 1LL * ret2 * pans % mod;
        }
        for (int T = 1, gx; T <= min(C, min(A, B)); T = gx + 1)
        {
            gx = min(A / (A / T), min(B / (B / T), C / (C / T)));
            int pans = fpow(1LL * func[2][gx] * fpow(func[2][T - 1], mod - 2) % mod, 1LL * (A / T) * (B / T) % (mod - 1) * (C / T) % (mod - 1));
            ret3 = 1LL * ret3 * pans % mod;
        }
        for (int T = 1, gx; T <= min(B, min(A, C)); T = gx + 1)
        {
            gx = min(A / (A / T), min(B / (B / T), C / (C / T)));
            int pans = fpow(1LL * func[2][gx] * fpow(func[2][T - 1], mod - 2) % mod, 1LL * (A / T) * (B / T) % (mod - 1) * (C / T) % (mod - 1));
            ret4 = 1LL * ret4 * pans % mod;
        }
        return 1LL * ret1 * ret2 % mod * fpow(1LL * ret3 * ret4 % mod, mod - 2) % mod;
    }

} // namespace Subtask3

int main()
{
    scanf("%d%d", &T, &mod), sieve();
    while (T--)
    {
        scanf("%d%d%d", &A, &B, &C);
        printf("%d %d %d\n", Subtask1::handler(), Subtask2::handler(), Subtask3::handler());
    }
    return 0;
}