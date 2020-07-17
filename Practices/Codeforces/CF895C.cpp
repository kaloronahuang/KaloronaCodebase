// CF895C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;
const int pi[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

int n, ai[80], cnt[80], masks[80], bin[MAX_N], dp[80][1 << 19];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 70; i++)
    {
        int acc = i, rk = 0;
        for (int x : pi)
        {
            while (acc % x == 0)
                acc /= x, masks[i] ^= (1 << rk);
            rk++;
        }
    }
    bin[0] = 1;
    for (int i = 1; i <= n; i++)
        bin[i] = 2LL * bin[i - 1] % mod;
    for (int i = 1, acc; i <= n; i++)
        scanf("%d", &acc), cnt[acc]++;
    dp[0][0] = 1;
    for (int i = 1; i <= 70; i++)
        for (int stat = 0; stat < (1 << 19); stat++)
            if (cnt[i])
                dp[i][stat] = 1LL * bin[cnt[i] - 1] * ((0LL + dp[i - 1][stat] + dp[i - 1][stat ^ masks[i]]) % mod) % mod;
            else
                dp[i][stat] = dp[i - 1][stat];
    printf("%lld\n", (0LL + mod + dp[70][0] - 1) % mod);
    return 0;
}