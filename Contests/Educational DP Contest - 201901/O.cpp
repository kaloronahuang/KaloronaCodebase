// O.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 22, mod = 1e9 + 7;

int n, dp[1 << MAX_N], tmp;
bool mapping[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &tmp), mapping[i][j] = (tmp == 1);
    dp[0] = 1;
    for (int i = 1; i < (1 << n); i++)
    {
        int counter = 0;
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1)
                counter++;
        for (int j = 0; j < n; j++)
            if (((i >> j) & 1) && mapping[counter][j + 1])
                dp[i] = (dp[i] + dp[i ^ (1 << j)]) % mod;
    }
    printf("%d", dp[(1 << n) - 1]);
    return 0;
}