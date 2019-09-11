// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int prefix[MAX_N][MAX_N], suffix[MAX_N][MAX_N];
int n, ai[MAX_N], bi[MAX_N], ci[MAX_N], m;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &ai[i], &bi[i], &ci[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < MAX_N; j++)
        {
            prefix[i][j] = prefix[i - 1][j];
            if (j >= ai[i])
                prefix[i][j] = max(prefix[i][j], prefix[i - 1][j - ai[i]] + bi[i]);
        }
    for (int i = n; i >= 1; i--)
        for (int j = 0; j < MAX_N; j++)
        {
            suffix[i][j] = suffix[i + 1][j];
            if (j >= ai[i])
                suffix[i][j] = max(suffix[i][j], suffix[i + 1][j - ai[i]] + bi[i]);
        }
    scanf("%d", &m);
    while (m--)
    {
        int del, money;
        scanf("%d%d", &del, &money), del++;
        int ans = 0;
        for (int i = 0; i <= money; i++)
            ans = max(ans, prefix[del - 1][i] + suffix[del + 1][money - i]);
        printf("%d\n", ans);
    }
    return 0;
}