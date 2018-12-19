// P2051.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int MX_N = 102, MOD = 9999973;
ll dp[MX_N][MX_N][MX_N], N, M;
ll C2(ll num)
{
    return (num * (num - 1)) / 2;
}
int main()
{
    scanf("%lld%lld", &N, &M);
    dp[0][0][0] = 1;
    for (int ln = 0; ln < N; ln++)
        for (int opit = 0; opit <= M; opit++)
            for (int tpit = 0; tpit + opit <= M; tpit++)
                if (dp[ln][opit][tpit])
                {
                    // 不放置棋子的情况;
                    // Situation without placing;
                    dp[ln + 1][opit][tpit] = (dp[ln + 1][opit][tpit] + dp[ln][opit][tpit]) % MOD;
                    // 在不放置棋子的位置上放置一个棋子;
                    // Situation of placing one on empty lines;
                    if (M - opit - tpit >= 1)
                        dp[ln + 1][opit + 1][tpit] = (dp[ln + 1][opit + 1][tpit] + dp[ln][opit][tpit] * (M - opit - tpit)) % MOD;
                    // 在放置了一个棋子的位置上放置一个棋子；
                    // Situation of placing one on lines with only piece;
                    if (opit >= 1)
                        dp[ln + 1][opit - 1][tpit + 1] = (dp[ln + 1][opit - 1][tpit + 1] + dp[ln][opit][tpit] * opit) % MOD;
                    // 在两个没有放置棋子的位置上放置两个棋子，其中 C2(num) = C^num_2;
                    // Situation of placing two pieces on the two empty slots;
                    if (M - opit - tpit >= 2)
                        dp[ln + 1][opit + 2][tpit] = (dp[ln + 1][opit + 2][tpit] + dp[ln][opit][tpit] * C2(M - opit - tpit)) % MOD;
                    // 在一个没有棋子的位置和一个有一个棋子的位置放置共两个棋子;
                    // Situation of placing one on the empty and another on the only slot;
                    if (M - opit - tpit >= 1 && opit >= 1)
                        dp[ln + 1][opit][tpit + 1] = (dp[ln + 1][opit][tpit + 1] + dp[ln][opit][tpit] * (M - opit - tpit) * opit) % MOD;
                    // 在两个一个棋子的位置放置共两个棋子;
                    // Situation of placing two on two only slots;
                    if (opit >= 2)
                        dp[ln + 1][opit - 2][tpit + 2] = (dp[ln + 1][opit - 2][tpit + 2] + dp[ln][opit][tpit] * C2(opit)) % MOD;
                }
    ll ans = 0;
    for (int i = 0; i <= M; i++)
        for (int j = 0; i + j <= M; j++)
            ans = (ans + dp[N][i][j]) % MOD;
    printf("%lld\n", ans);
    return 0;
}