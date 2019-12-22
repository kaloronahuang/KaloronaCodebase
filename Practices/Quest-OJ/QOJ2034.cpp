// QOJ2034.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e6 + 200, bas = 233, mod = 1e9 + 7;

int n, m, q, hash1[MAX_N], hash2[MAX_N], pw[MAX_N], perm[MAX_N];
ll aux[MAX_N], g1[MAX_N], g2[MAX_N];
char opt[20], A[MAX_N], B[MAX_N], t[MAX_N];

int getHash(int *hash_table, int l, int r)
{
    return (0LL + hash_table[r] + mod - 1LL * hash_table[l - 1] * pw[r - l + 1] % mod) % mod;
}

int manacher(char *str, int len)
{
    t[0] = '$', t[1] = '#';
    int j = 1;
    for (int i = 1; i <= len; i++)
        t[++j] = str[i], t[++j] = '#';
    t[j + 1] = 0;
    int tot = j + 1;
    int mid = 0, R = 0;
    for (int i = 1; i <= j; i++)
    {
        if (i < R)
            perm[i] = min(perm[mid * 2 - i], R - i);
        else
            perm[i] = 1;
        while (t[i - perm[i]] == t[i + perm[i]])
            perm[i]++;
        if (R < i + perm[i])
            R = i + perm[i], mid = i;
    }
    return tot;
}

void calc(char *str, int len, ll *g)
{
    memset(perm, 0, sizeof(perm));
    memset(aux, 0, sizeof(aux));
    int tot = manacher(str, len);
    for (int i = 1; i <= tot; i++)
        aux[i - perm[i] + 1]++, aux[i + 1]--;
    for (int i = 1; i <= tot + 1; i++)
        aux[i] += aux[i - 1];
    for (int i = 1; i <= len + 1; i++)
        g[i] = aux[i << 1];
    for (int i = 1; i <= len + 1; i++)
        g[i] += g[i - 1];
}

int LCP(int x, int y)
{
    int l = 0, r = min(n - x + 1, m - y + 1), res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (getHash(hash1, x, x + mid - 1) == getHash(hash2, y, y + mid - 1))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    return res;
}

int main()
{
    scanf("%s%s%s", opt, A + 1, B + 1);
    n = strlen(A + 1), m = strlen(B + 1);
    scanf("%d", &q), reverse(B + 1, B + 1 + m);
    for (int i = pw[0] = 1; i < MAX_N; i++)
        pw[i] = 1LL * pw[i - 1] * bas % mod;
    for (int i = 1; i <= n; i++)
        hash1[i] = (1LL * hash1[i - 1] * bas % mod + A[i] - 'a') % mod;
    for (int i = 1; i <= m; i++)
        hash2[i] = (1LL * hash2[i - 1] * bas % mod + B[i] - 'a') % mod;
    calc(A, n, g1), calc(B, m, g2);
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int len = LCP(x, y);
        printf("%lld\n", g1[x + len] - g1[x] + g2[y + len] - g2[y] + len);
    }
    return 0;
}