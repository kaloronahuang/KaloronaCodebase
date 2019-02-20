// P1736.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2600;
int n, m, arr[MAX_N][MAX_N], prefix[MAX_N][MAX_N], dp[MAX_N][MAX_N][2], ans = 0;
int read()
{
    int ans = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        ans = ans * 10 + ch - '0', ch = getchar();
    return f * ans;
}
int getRect(int x, int y, int a, int b) { return prefix[a][b] - prefix[x - 1][b] - prefix[a][y - 1] + prefix[x - 1][y - 1]; }
int main()
{
    bool flag = false;
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            arr[i][j] = read(), prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + arr[i][j], flag |= (arr[i][j] == 1) ? true : false;
    if (!flag)
        puts("0"), exit(0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            // judge if I can transfer from the top;
            int p = 1, q = 1;
            while (q)
            {
                int val = p + q;
                if (i - val + 1 >= 1 && j - val + 1 >= 1 && val - 1 <= dp[i - 1][j - 1][0] && getRect(i - val + 1, j - val + 1, i, j) - val == 0)
                    p += q, q <<= 1;
                else
                    q >>= 1;
            }
            dp[i][j][0] = p, ans = max(ans, p);
        }
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
        {
            // judge if I can transfer from the top;
            int p = 1, q = 1;
            while (q)
            {
                int val = p + q;
                if (i - val + 1 >= 1 && j + val - 1 <= m && val - 1 <= dp[i - 1][j + 1][1] && getRect(i - val + 1, j, i, j + val - 1) - val == 0)
                    p += q, q <<= 1;
                else
                    q >>= 1;
            }
            dp[i][j][1] = p, ans = max(ans, p);
        }
    printf("%d", ans);
    return 0;
}