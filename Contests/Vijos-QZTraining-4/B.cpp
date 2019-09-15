// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int n, m, val[MAX_N][MAX_N], prefix[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &val[i][j]), prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + val[i][j];
    int mx_ans = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        for (int k = 0; k < i; k++)
            for (int j = 0, min_val = 0x3f3f3f3f; j <= m; j++)
            {
                min_val = min(min_val, prefix[i][j] - prefix[k][j]);
                mx_ans = max(mx_ans, prefix[i][j] - prefix[k][j] - min_val);
                continue;
            }
    printf("%d", mx_ans);
    return 0;
}