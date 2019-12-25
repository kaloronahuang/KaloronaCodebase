// CF605E.cpp
#include <bits/stdc++.h>
typedef double ld;

using namespace std;

const int MAX_N = 1010;

int pi[MAX_N][MAX_N], n;
ld mp[MAX_N][MAX_N], dp[MAX_N], dom[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &pi[i][j]), mp[i][j] = ld(pi[i][j]) / 100.0;
    if (n == 1)
        puts("0"), exit(0);
    for (int i = 1; i <= n; i++)
        dp[i] = 1, dom[i] = (1.0 - mp[i][n]);
    dp[n] = 0, vis[n] = true;
    for (int i = 1; i <= n; i++)
    {
        int x = 0;
        ld mx = 1e18;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && dp[j] / (1 - dom[j]) < mx)
                mx = dp[j] / (1 - dom[j]), x = j;
        vis[x] = true;
        if (x == 1)
            printf("%.10lf", dp[1] / (1.0 - dom[1])), exit(0);
        for (int j = 1; j <= n; j++)
            dp[j] += (dp[x] / (1 - dom[x])) * mp[j][x] * dom[j], dom[j] *= (1 - mp[j][x]);
    }
    return 0;
}