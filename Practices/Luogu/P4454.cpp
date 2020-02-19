// P4454.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int g, mod, T, A, B;

int quick_pow(int bas, int tim)
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

int bsgs(int bas, int target)
{
    if (bas == 0 && target == 0)
        return 1;
    if (bas == 0 && target != 0)
        return -1;
    unordered_map<int, int> ump;
    int m = ceil(sqrt(mod));
    for (int j = 0, x = 1; j <= m; j++, x = 1LL * x * bas % mod)
        ump[1LL * x * target % mod] = j;
    int unit = quick_pow(bas, m);
    for (int j = 1, x = unit; j <= m; j++, x = 1LL * x * unit % mod)
        if (ump.count(x))
            return (j * m - ump[x]);
    return -1;
}

int main()
{
    scanf("%d%d%d", &g, &mod, &T);
    while (T--)
    {
        scanf("%d%d", &A, &B);
        int a = bsgs(g, A), b = bsgs(g, B);
        printf("%d\n", quick_pow(g, 1LL * a * b % (mod - 1)));
    }
    return 0;
}