// P1373.cpp
#include <iostream>

using namespace std;
// Variables;
const int maxn = 802;
const int INF = 0x7fffffff;
const int P = 1000000007;
int n, m, k;
int map[maxn][maxn];
int F[maxn][maxn][20][2];
// Start to dp;
void dp()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int h = 0; h <= k; h++)
            {
                F[i][j][h][0] = (F[i][j][h][0] + F[i - 1][j][(h - map[i][j] + k) % k][1]) % P;
                F[i][j][h][0] = (F[i][j][h][0] + F[i][j - 1][(h - map[i][j] + k) % k][1]) % P;
                F[i][j][h][1] = (F[i][j][h][1] + F[i - 1][j][(h + map[i][j]) % k][0]) % P;
                F[i][j][h][1] = (F[i][j][h][1] + F[i][j - 1][(h + map[i][j]) % k][0]) % P;
            }
}

int main()
{
    // Input;
    cin >> n >> m >> k, ++k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            // Initialize;
            cin >> map[i][j], F[i][j][map[i][j]][0] = 1;
    dp();
    long long ans = 0;
    // Calculate the answer;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans += F[i][j][0][1], ans %= P;
    // Output;
    cout << ans;
    return 0;
}