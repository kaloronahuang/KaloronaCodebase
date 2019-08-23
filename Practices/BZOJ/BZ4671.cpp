// BZ4671.cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 110, MAX_S = 65;

ll fac[MAX_N], linear_bas[61], answer = 0, stat[MAX_N], g[MAX_N];
int S, n, len, mp[MAX_S][MAX_N][MAX_N], aff[MAX_N], hbit;
char str[1005];
bool insert(ll x)
{
    for (ll i = hbit - 1; i >= 0; i--)
        if ((x >> i) & 1)
        {
            if (linear_bas[i] == 0)
            {
                linear_bas[i] = x;
                return true;
            }
            x ^= linear_bas[i];
        }
    return false;
}

void dfs(int x, int org)
{
    if (x == n + 1)
    {
        hbit = 0, memset(linear_bas, 0, sizeof(linear_bas));
        for (int curt_g = 1; curt_g <= S; curt_g++)
        {
            stat[curt_g] = hbit = 0;
            for (int i = 1; i <= n; i++)
                for (int j = i + 1; j <= n; j++)
                    if (aff[i] != aff[j])
                        stat[curt_g] |= (1LL * mp[curt_g][i][j] << hbit), hbit++;
        }
        int tot = 0;
        for (int curt_g = 1; curt_g <= S; curt_g++)
            if (!insert(stat[curt_g]))
                tot++;
        g[org] += (1LL << tot);
        return;
    }
    for (int i = 1; i <= org; i++)
        aff[x] = i, dfs(x + 1, org);
    aff[x] = org + 1, dfs(x + 1, org + 1);
}

int main()
{
    scanf("%lld", &S);
    for (int i = 1; i <= S; i++)
    {
        scanf("%s", str + 1), len = strlen(str + 1);
        if (n == 0)
            n = (1 + (int)(sqrt(8 * len + 1))) >> 1;
        int cur = 1;
        for (int x = 1; x <= n; x++)
            for (int y = x + 1; y <= n; y++)
                mp[i][x][y] = (str[cur++] == '1');
    }

    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * i * fac[i - 1];

    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        answer += 1LL * ((i & 1) ? 1LL : -1LL) * fac[i - 1] * g[i];
    printf("%lld", answer);
    return 0;
}