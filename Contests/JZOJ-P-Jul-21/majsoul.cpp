// majsoul.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;

int m, n, k, binom[5] = {1, 4, 6, 4, 1};

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
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

int main()
{
    // fileIO("majsoul");
    scanf("%d%d%d", &m, &n, &k);
    if (m == 1)
    {
        if (k == 0)
            printf("%d\n", 1LL * n * m % mod * 6 % mod);
        else
            puts("0");
        return 0;
    }
    else if (m == 2)
    {
        // subtask1;
        int ret = 1LL * n * m % mod * 6 % mod * fpow(4, k) % mod, denominator = 1;
        for (int i = n * m - k; i <= n * m - 1; i++)
            ret = 1LL * ret * i % mod;
        for (int i = 1; i <= k; i++)
            denominator = 1LL * denominator * i % mod;
        ret = 1LL * ret * fpow(denominator, mod - 2) % mod;
        printf("%d\n", ret);
        return 0;
    }
    else if (k <= 1)
    {
        // subtask2;
        int ret = 0;
        if (k == 0)
            ret = 1LL * n * m % mod * 6 % mod;
        else
        {
            int block = 1LL * n * m % mod;
            ret = 1LL * block * ((0LL + block + mod - 1) % mod) % mod * 6 % mod * 4 % mod;
        }
        printf("%d\n", ret);
    }
    return 0;
}