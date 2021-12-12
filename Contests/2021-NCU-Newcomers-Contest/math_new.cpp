// math_new.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 40, mod = 1e9 + 7;

int T, m, dp[MAX_N][10];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &m);
        // m = T + 1;
        int max_bit = 0;
        while ((1LL << max_bit) <= m)
            max_bit++;
        max_bit--;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        if (m & 2)
            dp[1][0] = 2;
        else
            dp[1][0] = 1, dp[1][1] = 1;
        for (int i = 2; i <= max_bit; i++)
        {
            int bit = ((m >> i) & 1);
            if (bit)
            {
                dp[i][0] = (0LL + 3LL * dp[i - 1][0] % mod + dp[i - 1][1]) % mod;
                dp[i][1] = (0LL + dp[i - 1][0] + 3LL * dp[i - 1][1] % mod + 3LL * dp[i - 1][2] % mod) % mod;
                dp[i][2] = dp[i - 1][2];
            }
            else
            {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = (0LL + 3LL * dp[i - 1][0] % mod + 3LL * dp[i - 1][1] % mod + dp[i - 1][2]) % mod;
                dp[i][2] = (0LL + dp[i - 1][1] + 3LL * dp[i - 1][2] % mod) % mod;
            }
            /*
            if (bit)
            {
                dp[i][0] = (0LL + 3LL * dp[i - 1][0] % mod + dp[i - 1][1]) % mod;
                dp[i][1] = (0LL + dp[i - 1][0] + 3LL * dp[i - 1][1] % mod + 3LL * dp[i - 1][2] % mod) % mod;
                dp[i][2] = dp[i - 1][2];
            }
            else
            {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = (0LL + 3LL * dp[i - 1][0] % mod + 3LL * dp[i - 1][1] % mod + dp[i - 1][2]) % mod;
                dp[i][2] = (0LL + dp[i - 1][1] + 3LL * dp[i - 2][2] % mod) % mod;
            }
            */
        }
        printf("%d\n", dp[max_bit][0]);
    }
    return 0;
}