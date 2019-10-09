// P5367.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int tree[MAX_N], fac, perm[MAX_N], ans, n;

inline int lowbit(int x) { return x & (-x); }

int query(int x)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += d;
}

int main()
{
    scanf("%d", &n), fac = 1;
    for (int i = n; i >= 1; i--)
        scanf("%d", &perm[i]);
    for (int i = 1, tmp = 0; i <= n; i++)
    {
        tmp = query(perm[i]);
        ans = (1LL * ans + 1LL * fac * tmp % mod) % mod, fac = 1LL * i * fac % mod;
        update(perm[i], 1);
    }
    printf("%d", (ans + 1) % mod);
    return 0;
}