// COGS56.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20100;

int T, n, prime[MAX_N], tot, dp[MAX_N], stp[MAX_N];
bool pt[MAX_N], vis[MAX_N];

void setFileIO()
{
    freopen("stonegame.in", "r", stdin);
    freopen("stonegame.out", "w", stdout);
}

int main()
{
    setFileIO();
    // sieve;
    for (int i = 2; i < MAX_N; i++)
    {
        for (int j = 1; j <= tot; j++)
            if (i % prime[j] == 0)
            {
                vis[i] = true;
                break;
            }
        if (!vis[i])
            prime[++tot] = i;
        stp[i] = tot;
    }
    for (int i = 2; i < MAX_N; i++)
        for (int j = stp[i]; j >= 1; j--)
            if (!pt[i - prime[j]])
            {
                pt[i] = true;
                break;
            }
    for (int i = 2; i < MAX_N; i++)
        if (pt[i])
        {
            dp[i] = 1e9;
            for (int j = stp[i]; j >= 1; j--)
                if (!pt[i - prime[j]])
                    dp[i] = min(dp[i], dp[i - prime[j]] + 1);
        }
        else
        {
            dp[i] = -1e9;
            for (int j = stp[i]; j >= 1; j--)
                if (pt[i - prime[j]])
                    dp[i] = max(dp[i], dp[i - prime[j]] + 1);
        }
    scanf("%d", &T);
    while (T--)
        scanf("%d", &n), printf("%d\n", (pt[n] == true) ? (dp[n]) : (-1));
    return 0;
}