// P2339.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxc = 1010;
const int maxt = 22000;
const int INF = 0x7fffffff;
int C, H, B, dp[maxc][maxc][2];
struct teacher
{
    int X, T, id;
    bool operator<(const teacher &t) const
    {
        return X < t.X;
    }
} ts[maxc];
int solve()
{
    fill(dp[0][0], dp[0][0] + maxc * maxc * 2, 1e9);
    dp[1][C][0] = max(ts[1].X, ts[1].T), dp[1][C][1] = max(ts[C].X, ts[C].T);
    for (int i = 1; i <= C; i++)
        for (int j = C; j >= i; j--)
        {
            dp[i][j][0] = min(dp[i][j][0], max(dp[i - 1][j][0] + abs(ts[i - 1].X - ts[i].X), ts[i].T));
            dp[i][j][0] = min(dp[i][j][0], max(dp[i][j + 1][1] + abs(ts[j + 1].X - ts[i].X), ts[i].T));
            dp[i][j][1] = min(dp[i][j][1], max(dp[i - 1][j][0] + abs(ts[i - 1].X - ts[j].X), ts[j].T));
            dp[i][j][1] = min(dp[i][j][1], max(dp[i][j + 1][1] + abs(ts[j + 1].X - ts[j].X), ts[j].T));
        }
    int ans = INF;
    for (int i = 1; i <= C; i++)
        ans = min(ans, min(dp[i][i][0], dp[i][i][1]) + abs(B - ts[i].X));
    return ans;
}
int main()
{
    cin >> C >> H >> B;
    for (int i = 1; i <= C; i++)
    {
        int x, t;
        cin >> x >> t;
        ts[i] = teacher{x, t, i};
    }
    sort(ts + 1, ts + C + 1);
    printf("%d", solve());
    return 0;
}