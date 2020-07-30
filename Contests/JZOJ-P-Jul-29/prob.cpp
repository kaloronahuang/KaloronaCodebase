// prob.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int n, m;

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
    /*
    freopen("prob.in", "r", stdin);
    freopen("prob.out", "w", stdout);
    */
    scanf("%d%d", &n, &m);
    int ans = 0;
    for (int j = 0, opt = 1, acc = 1; j <= n; j++, opt = mod - opt, acc = 1LL * acc * j % mod)
        ans = (0LL + ans + 1LL * opt * fpow(j, m) % mod * acc % mod) % mod;
    printf("%d\n", ans);
    return 0;
}