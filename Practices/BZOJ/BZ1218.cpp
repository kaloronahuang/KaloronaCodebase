// BZ1218.cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 5010;
int n, R, sum[maxn][maxn], xsiz, ysiz;
int main()
{
    cin >> n >> R;
    for (int i = 0; i < n; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;
        sum[x + 1][y + 1] = v;
    }
    sum[0][1] += sum[0][0];
    sum[1][0] += sum[0][0];
    for (int i = 1; i < maxn; i++)
        for (int j = 1; j < maxn; j++)
            sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
    int ans = 0;
    for (int i = R; i < maxn; i++)
        for (int j = R; j < maxn; j++)
            ans = max(ans, sum[i][j] - sum[i][j - R] - sum[i - R][j] + sum[i - R][j - R]);
    cout << ans;
    return 0;
}