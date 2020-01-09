// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, p, primes[MAX_N], cnt[MAX_N], ptot, cmod, pic[MAX_N], ai[MAX_N];

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y), t = x;
    x = y, y = t - (a / b) * y;
    return d;
}

int getInv(int a)
{
    int x, y;
    exgcd(a, cmod, x, y);
    return (x + cmod) % cmod;
}

int quick_pow(int bas, int tim)
{
    if (tim < 0)
        return quick_pow(getInv(bas), -tim);
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

int fac(int x, int mod)
{
    int ret = 1;
    for (int i = 1; i <= x; i++)
        if (i % mod != 0)
            ret = 1LL * ret * i % cmod;
    return ret;
}

int fac(int x, int mod, int &tot)
{
    // lucas;
    if (x < mod)
        return fac(x, mod);
    int seg = x / cmod, rem = x % cmod;
    int res = 1LL * quick_pow(fac(cmod - 1, mod), seg) * fac(rem, mod) % cmod;
    tot += x / mod;
    res = 1LL * res * fac(x / mod, mod, tot) % cmod;
    return res;
}

int binomial(int n_, int k_, int mod)
{
    int a = 0, b = 0, c = 0, res = 1;
    res = 1LL * res * fac(n_, mod, a) % cmod * getInv(fac(k_, mod, b)) % cmod * getInv(fac(n_ - k_, mod, c)) % cmod;
    return 1LL * res * quick_pow(mod, a - (b + c)) % cmod;
}

void factorize(int tmp)
{
    for (int i = 2; 1LL * i * i <= tmp; i++)
        if (tmp % i == 0)
        {
            primes[++ptot] = i;
            while (tmp % i == 0)
                cnt[ptot]++, tmp /= i;
        }
    if (tmp > 1)
        primes[++ptot] = tmp, cnt[ptot] = 1;
}

int main()
{
    scanf("%d%d%d", &n, &m, &p), n += m;
    factorize(p);
    for (int i = 1; i <= ptot; i++)
    {
        cmod = 0x7fffffff, cmod = pic[i] = quick_pow(primes[i], cnt[i]);
        ai[i] = binomial(n, m, primes[i]);
    }
    cmod = 0x7fffffff;
    // begins to merge;
    for (int i = 2; i <= ptot; i++)
    {
        int x, y;
        exgcd(pic[i - 1], pic[i], x, y);
        pic[i] *= pic[i - 1];
        ai[i] = ((1LL * x * (ai[i] - ai[i - 1]) * pic[i - 1] % pic[i] + ai[i - 1]) % pic[i] + pic[i]) % pic[i];
    }
    printf("%d\n", ai[ptot]);
    return 0;
}