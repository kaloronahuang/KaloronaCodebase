// CF1161D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 998244353;

int n, fa[MAX_N], val[MAX_N];
char str[MAX_N];
bool errorFlag = false;

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

const int inv2 = quick_pow(2, mod - 2);

void clear()
{
    for (int i = 0; i < MAX_N; i++)
        fa[i] = i, val[i] = 0;
}

int find(int x)
{
    if (fa[x] == x)
        return x;
    int v = fa[x];
    fa[x] = find(fa[x]), val[x] ^= val[v];
    return fa[x];
}

void merge(int x, int y, int v)
{
    find(x), find(y), v ^= val[x] ^ val[y], x = fa[x], y = fa[y];
    if (x != y)
        val[x] = v, fa[x] = y;
    else
        errorFlag |= val[x] ^ val[y] ^ v;
}

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    if (str[n] == '1')
        puts("0"), exit(0);
    int ans = 0;
    for (int sp = n - 1; sp >= 1; sp--)
    {
        errorFlag = false, clear();
        for (int i = 1; i <= (n >> 1); i++)
            merge(i, n - i + 1, 0);
        for (int i = 2; i <= n - sp; i++)
            if (str[i] != '?')
                merge(i, n, str[i] == '0');
        if (str[n - sp + 1] != '?')
            merge(n - sp + 1, n, str[n - sp + 1] == '1');
        int acc = inv2;
        for (int lptr = n - sp + 2, rptr = n - 1; lptr <= rptr; lptr++, rptr--)
            if (str[lptr] == str[rptr] && str[lptr] == '?')
                acc = 2LL * acc % mod;
            else if (str[lptr] != '?' && str[rptr] != '?')
                merge(lptr, rptr, str[lptr] != str[rptr]);
        acc = 1LL * acc * (errorFlag == false);
        for (int i = 1; i <= n; i++)
            if (find(i) == i)
                acc = 2LL * acc % mod;
        ans = (1LL * ans + acc) % mod;
    }
    printf("%d\n", ans);
    return 0;
}