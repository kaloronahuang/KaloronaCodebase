// ARC098A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int pre[2][MAX_N], n;
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= n; i++)
        pre[str[i] == 'E'][i]++, pre[0][i] += pre[0][i - 1], pre[1][i] += pre[1][i - 1];
    int ans = 1e9;
    for (int i = 1; i <= n; i++)
        ans = min(pre[0][i - 1] + pre[1][n] - pre[1][i], ans);
    printf("%d\n", ans);
    return 0;
}