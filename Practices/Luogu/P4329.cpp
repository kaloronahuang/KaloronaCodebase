// P4329.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21;

typedef long double cd;

int n, popcount[1 << MAX_N];
cd pi[MAX_N][MAX_N], dp[1 << MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &x), pi[i][j] = x / 100.0;
    for (int stat = 0; stat < (1 << n); stat++)
        popcount[stat] = popcount[stat >> 1] + (stat & 1);
    dp[0] = 1;
    for (int stat = 0; stat < (1 << n); stat++)
        for (int i = 1; i <= n; i++)
            if (!(stat & (1 << (i - 1))))
                dp[stat ^ (1 << (i - 1))] = max(dp[stat ^ (1 << (i - 1))], dp[stat] * pi[i][popcount[stat] + 1]);
    /*
    for (int i = 0; i < (1 << n); i++)
        printf("%.12Lf\n", 100 * dp[i]);
    */
    printf("%.12Lf\n", 100 * dp[(1 << n) - 1]);
    return 0;
}