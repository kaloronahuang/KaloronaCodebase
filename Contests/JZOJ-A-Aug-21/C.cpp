// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 55, INF = 0x3f3f3f3f;

int mp[MAX_N][MAX_N], dp[(1 << 24)], n, m, ans;
int statA, statB, id[MAX_N];
ll con[MAX_N], dev[MAX_N];

int lowbit(int x) { return x & (-x); }

int count_bit(ll num)
{
    int ans = 0;
    for (; num; num -= lowbit(num))
        ans++;
    return ans;
}

int main()
{
    memset(mp, -1, sizeof(mp)), memset(id, -1, sizeof(id));
    scanf("%d%d", &n, &m);
    for (int i = 1, tmpx, tmpy, tmpz; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), mp[tmpx][tmpy] = mp[tmpy][tmpx] = tmpz;
    for (int i = 2; i <= n; i++)
        if (mp[1][i] != -1)
        {
            id[i] = ++statA, ans += (mp[1][i] ^ 1);
            for (int j = 2; j <= n; j++)
                if (mp[1][j] == -1 && mp[i][j] != -1)
                {
                    id[j] = (id[j] == -1) ? ++statB : id[j];
                    con[id[i]] |= 1LL << (id[j] - 1);
                    dev[id[i]] |= (1LL * (mp[1][i] ^ mp[i][j] ^ 1)) << (id[j] - 1);
                }
        }
    if (statA <= 20)
    {
        for (int i = 0; i < (1 << statA); i++)
            dp[i] = -INF;
        dp[0] = 0;
        for (int i = 0; i < (1 << statA); i++)
            if (dp[i] >= 0)
            {
                ll cur = 0;
                for (int j = 0; j < statA; j++)
                    if ((i >> j) & 1)
                        cur |= con[j + 1];
                for (int j = 0; j < statA; j++)
                    if (!((i >> j) & 1))
                    {
                        int nxt = i | (1 << j), num = dp[i] + __builtin_popcountll(dev[j + 1] & (~cur));
                        if (dp[nxt] < num)
                            dp[nxt] = num;
                    }
            }
        ans += dp[(1 << statA) - 1];
    }
    else
    {
        for (int i = 0; i < (1 << statB); i++)
            dp[i] = -INF;
        dp[0] = 0;
        for (int i = 0; i < (1 << statB); i++)
            if (dp[i] >= 0)
                for (int j = 0; j < statA; j++)
                    if ((i | con[j + 1]) != i)
                    {
                        int nxt = (i | con[j + 1]), num = dp[i] + __builtin_popcountll(dev[j + 1] & (~i));
                        dp[nxt] = max(dp[nxt], num);
                    }
        ans += dp[(1 << statB) - 1];
    }
    printf("%d", ans);

    return 0;
}