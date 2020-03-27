// ARC099F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 501000, mod = 998244353;

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

const int base[4] = {133, 233, 911, 691}, base_inv[4] = {fpow(base[0], mod - 2), fpow(base[1], mod - 2), fpow(base[2], mod - 2), fpow(base[3], mod - 2)};

struct node
{
    int val[4];

    bool operator<(const node &rhs) const
    {
        for (int i = 0; i < 4; i++)
            if (val[i] != rhs.val[i])
                return (val[i] < rhs.val[i]);
        return false;
    }

    bool operator==(const node &rhs) const
    {
        for (int i = 0; i < 4; i++)
            if (val[i] != rhs.val[i])
                return false;
        return true;
    }
} prefix[MAX_N], base_pre;

map<node, int> cnt;
int n, base_pow[MAX_N][4], base_invs[MAX_N][4], pos[MAX_N];
char str[MAX_N];

int getPow(int idx, int j) { return idx >= 0 ? base_pow[idx][j] : base_invs[-idx][j]; }

node calc(node x, node y, int idx)
{
    for (int i = 0; i < 4; i++)
        x.val[i] = (0LL + x.val[i] + 1LL * y.val[i] * getPow(idx, i) % mod) % mod;
    return x;
}

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int j = 0; j < 4; j++)
        for (int i = base_pow[0][j] = base_invs[0][j] = 1; i <= n; i++)
            base_pow[i][j] = 1LL * base_pow[i - 1][j] * base[j] % mod, base_invs[i][j] = 1LL * base_invs[i - 1][j] * base_inv[j] % mod;
    for (int j = 0; j < 4; j++)
        for (int i = 1, ptr = 0; i <= n; i++)
        {
            if (str[i] == '+')
                base_pre.val[j] = (0LL + base_pre.val[j] + getPow(ptr, j)) % mod;
            else if (str[i] == '-')
                base_pre.val[j] = (0LL + base_pre.val[j] + mod - getPow(ptr, j)) % mod;
            else if (str[i] == '<')
                ptr--;
            else
                ptr++;
            prefix[i].val[j] = base_pre.val[j], pos[i] = ptr;
        }
    cnt[base_pre]++;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += cnt[prefix[i]], cnt[calc(prefix[i], base_pre, pos[i])]++;
    printf("%lld\n", ans);
    return 0;
}