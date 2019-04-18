// POJ1185.cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, m, ans, dp[(1 << 10)][(1 << 10)][3], a[105], sum[(1 << 10)];
char str[20];
int getsum(int S)
{
    int tot = 0;
    while (S)
    {
        if (S & 1)
            tot++;
        S >>= 1;
    }
    return tot;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", str);
        for (int j = 0; j < m; j++)
            a[i] <<= 1, a[i] += (str[j] == 'H' ? 1 : 0);
    }
    for (int i = 0; i < (1 << m); i++)
        sum[i] = getsum(i);
    for (int S = 0; S < (1 << m); S++)
        if (!(S & a[0] || (S & (S << 1)) || (S & (S << 2))))
            dp[0][S][0] = sum[S];
    for (int L = 0; L < (1 << m); L++)
        for (int S = 0; S < (1 << m); S++)
            if (!(L & S || L & a[0] || S & a[1] || (L & (L << 1)) || (L & (L << 2)) || (S & (S << 1)) || (S & (S << 2))))
                dp[L][S][1] = sum[S] + sum[L];
    for (int i = 2; i < n; i++)
        for (int L = 0; L < (1 << m); L++)
        {
            if (L & a[i - 1] || (L & (L << 1)) || (L & (L << 2)))
                continue;
            for (int S = 0; S < (1 << m); S++)
            {
                if (S & a[i] || L & S || (S & (S << 1)) || (S & (S << 2)))
                    continue;
                for (int FL = 0; FL < (1 << m); FL++)
                {
                    if (FL & L || FL & S || FL & a[i - 2] || (FL & (FL << 1)) || (FL & (FL << 2)))
                        continue;
                    dp[L][S][i % 3] = max(dp[L][S][i % 3], dp[FL][L][(i - 1) % 3] + sum[S]);
                }
            }
        }
    for (int L = 0; L < (1 << m); L++)
        for (int S = 0; S < (1 << m); S++)
            ans = max(ans, dp[L][S][(n - 1) % 3]);
    printf("%d", ans);
    return 0;
}