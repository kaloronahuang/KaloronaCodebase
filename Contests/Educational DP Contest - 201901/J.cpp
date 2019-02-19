// J.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 330;
int n, ai[MAX_N], sushi[4];
double dp[MAX_N][MAX_N][MAX_N];
double dfs(int a, int b, int c)
{
    if (a == 0 && b == 0 && c == 0)
        return 0;
    if (dp[a][b][c] >= 0)
        return dp[a][b][c];
    double d = a + b + c, ans = n / d;
    if (a)
        ans += dfs(a - 1, b, c) * a / d;
    if (b)
        ans += dfs(a + 1, b - 1, c) * b / d;
    if (c)
        ans += dfs(a, b + 1, c - 1) * c / d;
    return dp[a][b][c] = ans;
}
int main()
{
    memset(dp, -1, sizeof(dp));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), sushi[ai[i]]++;
    printf("%.10lf", dfs(sushi[1], sushi[2], sushi[3]));
    return 0;
}