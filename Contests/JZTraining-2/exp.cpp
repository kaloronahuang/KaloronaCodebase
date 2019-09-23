// exp.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200, MAX_M = MAX_N + 32, MAX_B = 255;

int x, n, p;
double dp[MAX_N + 1][MAX_B + 1][MAX_M + 1][2];

void init()
{
    int up_bound = x >> 8;
    int bit = up_bound & 1, cnt = 0;
    while (up_bound && (up_bound & 1) == bit)
        up_bound >>= 1, cnt++;
    dp[0][x & MAX_B][cnt][bit] = 1.0;
}

int main()
{
    /*
    freopen("exp.in", "r", stdin);
    freopen("exp.out", "w", stdout);
    */
    scanf("%d%d%d", &x, &n, &p);
    double p1 = p * 0.01, p2 = 1.0 - p1;
    init();
    for (int i = 0; i < n; i++)
        for (int stat = 0; stat <= MAX_B; stat++)
            for (int j = 0; j < MAX_M; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    double now = dp[i][stat][j][k];

                    int bit = stat >> 7 & 1;
                    int cnt = (bit == k) ? (j + 1) : 1;
                    dp[i + 1][stat << 1 & MAX_B][cnt][bit] += now * p1;

                    bit = (stat == MAX_B) ? !k : k;
                    cnt = (stat == MAX_B && !k) ? 1 : j;
                    dp[i + 1][stat + 1 & MAX_B][cnt][bit] += now * p2;
                }
            }
    // now for the expectation;
    double res = 0;
    for (int stat = 0; stat <= MAX_B; stat++)
        for (int i = 0; i < MAX_M; i++)
            for (int j = 0; j < 2; j++)
                res += dp[n][stat][i][j] * (stat ? __builtin_ctz(stat) : 8 + (j ? 0 : i));
    printf("%.13lf\n", res);
    return 0;
}