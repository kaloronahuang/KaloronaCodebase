// FOJ5030.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30;

int T;
bool dp[141][57][29][15];
bool vis[141][57][29][15];

void fileIO()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
}

int read(int mod)
{
    static char str[int(1e4) + 200];
    scanf("%s", str + 1);
    int ret = 0;
    for (int i = 1; str[i]; i++)
        ret = (ret * 10 + str[i] - '0') % mod;
    return ret;
}

bool dfs(int a, int b, int c, int d)
{
    if (vis[a][b][c][d])
        return dp[a][b][c][d];
    if (a > 0)
        dp[a][b][c][d] |= !dfs(a - 1, b, c, d);
    if (b > 1)
        dp[a][b][c][d] |= !dfs(a, b - 2, c, d);
    if (c > 2)
        dp[a][b][c][d] |= !dfs(a, b, c - 3, d);
    if (d > 3)
        dp[a][b][c][d] |= !dfs(a, b, c, d - 4);
    if (b > 0 && a + 2 < 141)
        dp[a][b][c][d] |= !dfs(a + 2, b - 1, c, d);
    if (c > 0 && a + 1 < 141 && b + 1 < 57)
        dp[a][b][c][d] |= !dfs(a + 1, b + 1, c - 1, d);
    if (d > 0)
    {
        if (b + 2 < 57)
            dp[a][b][c][d] |= !dfs(a, b + 2, c, d - 1);
        if (a + 1 < 141 && c + 1 < 29)
            dp[a][b][c][d] |= !dfs(a + 1, b, c + 1, d - 1);
    }
    vis[a][b][c][d] = true;
    return dp[a][b][c][d];
}

int main()
{
    // fileIO();
    scanf("%d", &T);
    while (T--)
    {
        int a = read(2), b = read(3), c = read(2), d = read(3);
        // scanf("%d%d%d%d", &a, &b, &c, &d);
        // puts(dfs(a, b, c, d) ? "1" : "0");
        puts((a + c) % 2 != (b + d) % 3 ? "1" : "0");
    }
    return 0;
}