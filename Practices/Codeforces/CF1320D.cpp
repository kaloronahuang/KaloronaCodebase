// CF1320D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, bitnum = 133, mod = 1e9 + 7;

int n, q, pre[2][MAX_N], pownum[MAX_N], zeros[MAX_N];
char str[MAX_N];

int query(int l, int r, int opt) { return (0LL + pre[opt][r] + mod - 1LL * pre[opt][l - 1] * pownum[zeros[r] - zeros[l - 1]] % mod) % mod; }

int main()
{
    scanf("%d%s", &n, str + 1);
    pre[0][0] = pre[1][0] = pownum[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        zeros[i] = zeros[i - 1] + (str[i] == '0');
        pownum[i] = 1LL * pownum[i - 1] * bitnum % mod;
        pre[0][i] = pre[0][i - 1], pre[1][i] = pre[1][i - 1];
        if (str[i] == '0')
        {
            pre[0][i] = (0LL + 1LL * pre[0][i] * bitnum % mod + '0' + (i & 1)) % mod;
            pre[1][i] = (0LL + 1LL * pre[1][i] * bitnum % mod + '0' + ((i & 1) ^ 1)) % mod;
        }
    }
    scanf("%d", &q);
    while (q--)
    {
        int l1, l2, len;
        scanf("%d%d%d", &l1, &l2, &len);
        if (query(l1, l1 + len - 1, l1 & 1) == query(l2, l2 + len - 1, l2 & 1))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}