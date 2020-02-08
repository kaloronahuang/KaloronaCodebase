// BZ3328.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int T, m, mod, ptot, primes[MAX_N], g, wns[MAX_N];
ll n;

struct matrix
{
    int mat[2][2];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator+(const matrix &rhs)
    {
        matrix ret;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                ret[i][j] = (1LL * mat[i][j] + rhs.mat[i][j]) % mod;
        return ret;
    }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator*(const int &rhs)
    {
        matrix ret;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                ret[i][j] = 1LL * mat[i][j] * rhs % mod;
        return ret;
    }

    matrix operator^(const ll &rhs);
} eps, fib;

matrix matrix::operator^(const ll &rhs)
{
    ll tim = rhs;
    matrix ret = eps, bas = *this;
    while (tim)
    {
        if (tim & 1LL)
            ret = ret * bas;
        bas = bas * bas;
        tim >>= 1;
    }
    return ret;
}

int quick_pow(int bas, int tim, int cmod)
{
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

void find_root()
{
    ptot = 0;
    int x = mod - 1;
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            primes[++ptot] = i;
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        primes[++ptot] = x;
    for (int i = 2; i <= mod - 1; i++)
    {
        bool flag = true;
        for (int k = 1; flag && k <= ptot; k++)
            if (quick_pow(i, (mod - 1) / primes[k], mod) == 1)
                flag = false;
        if (flag)
        {
            g = i;
            break;
        }
    }
    int wn = quick_pow(g, (mod - 1) / m, mod);
    wns[0] = 1;
    for (int i = 1; i < m; i++)
        wns[i] = 1LL * wns[i - 1] * wn % mod;
}

int main()
{
    for (int i = 0; i < 2; i++)
        eps.mat[i][i] = 1;
    fib[0][0] = fib[0][1] = fib[1][0] = 1;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%d%d", &n, &m, &mod), find_root();
        matrix ans;
        ans.clear();
        for (int i = 0; i < m; i++)
            ans = ans + ((fib * wns[i] + eps) ^ n);
        printf("%lld\n", 1LL * ans[0][0] * quick_pow(m, mod - 2, mod) % mod);
    }
    return 0;
}