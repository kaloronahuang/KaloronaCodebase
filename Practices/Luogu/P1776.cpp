// P1776.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_M = 1e6 + 200;

int tot, n, m, vi[MAX_N * 20], wi[MAX_N * 20], dp[MAX_M];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int val, weight, cnt;
        scanf("%d%d%d", &val, &weight, &cnt);
        int p = 0;
        while ((1 << p) <= cnt)
        {
            cnt -= (1 << p);
            vi[++tot] = val * (1 << p), wi[tot] = weight * (1 << p);
            p++;
        }
        if (cnt)
            vi[++tot] = val * cnt, wi[tot] = weight * cnt;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = m; j >= wi[i]; j--)
            dp[j] = max(dp[j], dp[j - wi[i]] + vi[i]);
    printf("%d", dp[m]);
    return 0;
}