// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

int n, len, m, digits[MAX_N * MAX_N], dp[MAX_N * MAX_N][2][2];
char str[MAX_N * MAX_N];

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

const int inv2 = quick_pow(2, mod - 2);

int main()
{
    scanf("%d%s", &n, str + 1), len = n * n;
    for (int i = 1; i <= len; i++)
        digits[i] = str[i] - '0', m = (1LL * m * 10 % mod + digits[i]) % mod;
    int last_digit;
    dp[0][1][0] = 1;
    for (int i = 0; i <= len - 1; i++)
        for (int bit = 0; bit <= 1; bit++)
        {
            last_digit = bit ? digits[i + 1] : 9;
            for (int k = 0; k <= last_digit; k++)
            {
                dp[i + 1][bit && (k == last_digit)][(k <= digits[len - i]) ? 0 : 1] =
                    (dp[i + 1][bit && (k == last_digit)][(k <= digits[len - i]) ? 0 : 1] + dp[i][bit][0]) % mod;
                dp[i + 1][bit && (k == last_digit)][(k < digits[len - i]) ? 0 : 1] =
                    (dp[i + 1][bit && (k == last_digit)][(k < digits[len - i]) ? 0 : 1] + dp[i][bit][1]) % mod;
            }
        }
    int firstTerm = (0LL + dp[len][0][0] + dp[len][1][0]) % mod;
    int secondTerm = (0LL + dp[len >> 1][0][0] + dp[len >> 1][0][1] + dp[len >> 1][1][0]) % mod;
    int ans = (0LL + m + mod - 1LL * (firstTerm + mod - secondTerm) % mod * inv2 % mod) % mod;
    printf("%d\n", ans);
    return 0;
}