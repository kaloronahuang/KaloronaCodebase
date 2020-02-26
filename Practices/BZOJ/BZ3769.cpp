// BZ3769.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 660, mod = 1000000007;

int T, n, h, dp[MAX_N][MAX_N];

int search(int N, int H)
{
    if (N == 0)
        return 1;
    if (H == 0)
        return N == 1;
    if (dp[N][H] != -1)
        return dp[N][H];
    dp[N][H] = 0;
    for (int i = 1; i <= N; i++)
        dp[N][H] = (0LL + dp[N][H] + 1LL * search(i - 1, H - 1) * search(N - i, H - 1) % mod) % mod;
    return dp[N][H];
}

int main()
{
    memset(dp, -1, sizeof(dp));
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &h);
        printf("%lld\n", (0LL + search(n, h) + mod - (h <= 0 ? 0 : search(n, h - 1))) % mod);
    }
    return 0;
}