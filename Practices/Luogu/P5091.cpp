// P5091.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e7 + 200;

int a, m, b;
char str[MAX_N];

int phi(int x)
{
    int ret = x;
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            ret -= ret / i;
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        ret -= ret / x;
    return ret;
}

int fpow(int bas, int tim, int cmod)
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

int main()
{
    scanf("%d%d%s", &a, &m, str + 1);
    int mod = phi(m);
    bool flag = false;
    for (int i = 1; str[i]; i++)
    {
        b = b * 10 + str[i] - '0';
        if (b >= mod)
            flag = true, b %= mod;
    }
    int idx = b + (flag ? mod : 0);
    printf("%d\n", fpow(a, idx, m));
    return 0;
}