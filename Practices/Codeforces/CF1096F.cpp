// CF1096F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, m, perm[MAX_N], slot[MAX_N], nodes[MAX_N];

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x >= 1; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

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

int main()
{
    const int inv2 = quick_pow(2, mod - 2);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &perm[i]);
        if (perm[i] == -1)
            m++, slot[i]++;
    }
    for (int i = 1; i <= n; i++)
        slot[i] += slot[i - 1];
    int ans = 0;
    // stage 1;
    for (int i = n; i >= 1; i--)
        if (perm[i] != -1)
            ans = (1LL * ans + query(perm[i])) % mod, update(perm[i], 1);
    // stage 2;
    ans = (1LL * ans + 1LL * m * (m - 1) % mod * inv2 % mod * inv2 % mod) % mod;
    // stage 3;
    int invm = quick_pow(m, mod - 2);
    for (int i = 1; i <= n; i++)
        if (perm[i] != -1)
        {
            ans = (1LL * ans + 1LL * slot[i] * (m - perm[i] + query(perm[i])) % mod * invm % mod) % mod;
            ans = (1LL * ans + 1LL * (m - slot[i]) * (perm[i] - query(perm[i])) % mod * invm % mod) % mod;
        }
    printf("%d\n", ans);
    return 0;
}