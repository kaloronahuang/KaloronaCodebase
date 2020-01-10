// FOJ3784.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;
typedef long long ll;

int n, m, xi[MAX_N];
ll dp[MAX_N][33][2], prefix[MAX_N];

void fileIO()
{
    freopen("post.in", "r", stdin);
    freopen("post.out", "w", stdout);
}

int main()
{
    // fileIO();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &xi[i]);
    sort(xi + 1, xi + 1 + n);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + xi[i];
    memset(dp, 0x3f, sizeof(dp)), dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i][0][0] = 0, dp[i][1][1] = xi[i] * i - prefix[i];
        for (int j = 1; j <= min(i, m); j++)
            for (int k = i - 1; k >= 1 && k >= j - 1; k--)
                dp[i][j][0] = min(dp[i][j][0], dp[k][j][1] + (prefix[i] - prefix[k]) - xi[k] * (i - k));
        for (int j = 2; j <= min(i, m); j++)
        {
            long long lsum = 0;
            for (int k = i - 1, lptr = i - 1; k >= 0 && k >= j - 1; k--)
            {
                while (lptr >= max(k, 1) && xi[i] - xi[lptr] <= xi[lptr] - xi[k])
                    lsum += xi[i] - xi[lptr], lptr--;
                dp[i][j][1] = min(dp[i][j][1], dp[k][j - 1][1] + (prefix[lptr] - prefix[k]) - (lptr - k) * xi[k] + lsum);
            }
        }
    }
    printf("%lld\n", min(dp[n][m][0], dp[n][m][1]));
    return 0;
}