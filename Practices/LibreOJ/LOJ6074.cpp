// LOJ6074.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, q, pre[MAX_N][10], pre_inv[MAX_N][10], trans[10][10], S[10];
char str[MAX_N];

int main()
{
    scanf("%s%d", str + 1, &q), n = strlen(str + 1);
    for (int i = 0; i <= 9; i++)
        trans[i][i] = S[i] = pre[0][i] = 1;
    for (int i = 1; i <= n; i++)
    {
        int typ = str[i] - 'a' + 1, tmp;
        for (int j = 0; j <= 9; j++)
            tmp = trans[j][typ], trans[j][typ] = S[j], S[j] = (2LL * S[j] + mod - tmp) % mod;
        memcpy(pre[i], S, sizeof(pre[i]));
    }
    memset(trans, 0, sizeof(trans)), memset(S, 0, sizeof(S));
    for (int i = 0; i <= 9; i++)
        trans[i][i] = 1;
    pre_inv[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int typ = str[i] - 'a' + 1, tmp;
        for (int j = 0; j <= 9; j++)
            tmp = (0LL + trans[typ][j] + S[j]) % mod, S[j] = (0LL + S[j] + mod - tmp) % mod, trans[typ][j] = (0LL + trans[typ][j] + tmp) % mod;
        for (int j = 0; j <= 9; j++)
            pre_inv[i][j] = (0LL + trans[0][j] + S[j]) % mod;
    }
    while (q--)
    {
        int ans = mod - 1, l, r;
        scanf("%d%d", &l, &r);
        for (int i = 0; i <= 9; i++)
            ans = (0LL + ans + 1LL * pre[r][i] * pre_inv[l - 1][i] % mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}