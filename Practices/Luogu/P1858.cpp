// P1858.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int dp[55][MAX_N], k, m, n, wi[MAX_N], vi[MAX_N], tmp[MAX_N];

int main()
{
    scanf("%d%d%d", &k, &m, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &wi[i], &vi[i]);
    memset(dp, 128, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= wi[i]; j--)
        {
            int ptr1 = 1, ptr2 = 1, ptr = 0;
            while (ptr <= k)
                if (dp[ptr1][j] > dp[ptr2][j - wi[i]] + vi[i])
                    tmp[++ptr] = dp[ptr1++][j];
                else
                    tmp[++ptr] = dp[ptr2++][j - wi[i]] + vi[i];
            for (int pt = 1; pt <= k; pt++)
                dp[pt][j] = tmp[pt];
        }
    int ans = 0;
    for (int i = 1; i <= k; i++)
        ans += dp[i][m];
    printf("%d", ans);
    return 0;
}