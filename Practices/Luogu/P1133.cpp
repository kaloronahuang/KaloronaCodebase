// P1133.cpp
#include <iostream>
using namespace std;

const int maxn = 100010;
int n;
int dp[4][maxn][2];
int pos[4][maxn];
int ans = 0;

void preDP()
{
    for (int head = 1; head <= 3; head++)
    {
        for (int tim = 1; tim < 4; tim++)
            for (int s = 0; s < 2; s++)
                dp[tim][1][s] = 0;
        dp[head][1][0] = dp[head][1][1] = pos[head][1];
        for (int i = 2; i <= n; i++)
        {
            dp[1][i][0] = max(dp[2][i - 1][1], dp[3][i - 1][1]) + pos[1][i];
            dp[2][i][0] = dp[3][i - 1][1] + pos[2][i];
            dp[2][i][1] = dp[1][i - 1][0] + pos[2][i];
            dp[3][i][1] = max(dp[1][i - 1][0], dp[2][i - 1][0]) + pos[3][i];
        }
        for (int tim = 1; tim < head; tim++)
            ans = max(ans, dp[tim][n][0]);
        for (int tim = 3; tim > head; tim--)
            ans = max(ans, dp[tim][n][1]);
    }
}

void print()
{
    for (int j = 1; j <= 3; j++)
    {
        for (int i = 0; i <= 2 * n; i++)
            cout << dp[j][i] << " ";
        cout << endl;
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> pos[1][i] >> pos[2][i] >> pos[3][i];
    preDP();
    cout << ans;
    return 0;
}