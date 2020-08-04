// FOJ3211.cpp
#include <bits/stdc++.h>

using namespace std;

int fpow(int bas, int tim, int mod)
{
    if (tim < 0)
        return fpow(fpow(bas, mod - 2, mod), -tim, mod);
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

int bsgs(int a, int b, int mod)
{
    unordered_map<int, int> ump;
    int m = sqrt(mod), bas = fpow(a, mod - 2, mod), acc = b;
    for (int i = 0; i < m; i++, acc = 1LL * acc * bas % mod)
        if (ump.count(acc) == 0)
            ump[acc] = i;
    bas = fpow(a, m, mod), acc = 1;
    for (int i = 0; i <= m; i++, acc = 1LL * acc * bas % mod)
        if (ump.count(acc))
            return i * m + ump[acc];
    return -2;
}

int main()
{
    int T, p, a, b, x1, t;
    /*
    p = 7, a = 2, b = 2, x1 = 2;
    int a_n = x1, test = 0;
    for (int i = 2; i <= 20; i++)
    {
        // test = ((0LL + x1 + fpow(a - 1, p - 2, p)) % p * fpow(a, i - 1, p) % p + p - 1LL * b * fpow(a - 1, p - 2, p) % p) % p;
        test = (1LL * fpow(a, i - 1, p) * x1 % p + 1LL * b * fpow(a - 1, p - 2, p) % p * (fpow(a, i - 1, p) + p - 1) % p) % p;
        a_n = (1LL * a_n * a % p + b) % p;
        cerr << a_n << " " << test << endl;
    }
    */
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d%d", &p, &a, &b, &x1, &t);
        if (x1 == t)
        {
            puts("1");
            continue;
        }
        if (a == 1)
        {
            // x_i = x_1 + (i - 1)b = t;
            // t - x_1 + b = ib
            int target = (0LL + t + p - x1 + b) % p;
            if (b == 0)
                puts("-1");
            else
            {
                int ret = 1LL * target * fpow(b, p - 2, p) % p;
                if (ret == 0)
                    ret += p;
                printf("%lld\n", ret);
            }
            continue;
        }
        if (a == 0)
        {
            if (t == x1)
                puts("1");
            else if (t == b)
                puts("2");
            else
                puts("-1");
            continue;
        }
        int coeff = (0LL + x1 + 1LL * b * fpow(a - 1, p - 2, p) % p) % p;
        int target = (0LL + t + 1LL * b * fpow(a - 1, p - 2, p) % p) % p;
        target = 1LL * target * fpow(coeff, p - 2, p) % p;
        int n_1 = bsgs(a, target, p);
        printf("%d\n", n_1 + 1);
    }
    return 0;
}