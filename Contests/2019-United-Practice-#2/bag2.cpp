// bag2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 20, mod = 1e9 + 7;

int n, q, P, vi[MAX_N], tmpx;
bool dp[(1 << 11)][300];

int getNum(int num)
{
    while (num < 0)
        num += P;
    return num % P;
}

int main()
{
    freopen("bag2.in", "r", stdin);
    freopen("bag2.out", "w", stdout);
    scanf("%d%d%d", &n, &q, &P);
    for (int i = 1; i <= n; i++)
        scanf("%d", &vi[i]);
    if (n == 1)
    {
        while (q--)
        {
            scanf("%d", &tmpx);
            if (tmpx == 0)
                puts("2");
            else
                puts("1");
        }
        return 0;
    }
    else
    {
        sort(vi + 1, vi + 1 + n);
        dp[0][0] = true;
        for (int stat = 1; stat < (1 << n); stat++)
            for (int j = 0; j < P; j++)
                for (int i = 1; i <= n; i++)
                    if (stat & (1 << (i - 1)))
                        for (int k = 1; k < P; k++)
                        {
                            int num = j - k * vi[i];
                            while (num < 0)
                                num += P;
                            num %= P;
                            dp[stat][j] |= dp[stat ^ (1 << (i - 1))][num];
                        }
        while (q--)
        {
            scanf("%d", &tmpx), tmpx %= P;
            int ans = 0;
            for (int i = 0; i < (1 << n); i++)
                if (dp[i][tmpx])
                    ans = (1LL * ans + 1) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}