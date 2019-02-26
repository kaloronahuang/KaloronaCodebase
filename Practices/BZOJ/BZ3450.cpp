// BZ3450.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 300200;
int n;
char str[MAX_N];
long double dp[MAX_N], ans;
int main()
{
    scanf("%d%s", &n, str + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        switch (str[i])
        {
        case 'o':
            dp[i] = dp[i - 1] + 1;
            ans += 2 * dp[i - 1] + 1;
            break;
        case 'x':
            dp[i] = 0;
            break;
        case '?':
            dp[i] = 1.0 * (dp[i - 1] + 1) / 2.0;
            ans += 1.0 * (2.0 * dp[i - 1] + 1) / 2.0;
            break;
        }
    printf("%.4Lf", ans);
    return 0;
}