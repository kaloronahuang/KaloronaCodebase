// CF1257E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 2000;

int k[4], n, prefix[4][MAX_N], seq[4][MAX_N], min_val[MAX_N];

int main()
{
    scanf("%d%d%d", &k[1], &k[2], &k[3]), n = k[1] + k[2] + k[3];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= k[i]; j++)
            scanf("%d", &seq[i][j]), prefix[i][seq[i][j]]++;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= n; j++)
            prefix[i][j] += prefix[i][j - 1];
    for (int i = 0; i <= n; i++)
        min_val[i] = prefix[3][i] - prefix[2][i];
    for (int i = n - 1; i >= 0; i--)
        min_val[i] = min(min_val[i + 1], min_val[i]);
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= n; i++)
        ans = min(ans, prefix[2][i] - prefix[1][i] + min_val[i] + prefix[1][n] + prefix[2][n]);
    printf("%d\n", ans);
    return 0;
}