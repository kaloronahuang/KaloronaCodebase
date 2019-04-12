// F.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 550;
int dp[MAX_N][MAX_N], n;
char str[MAX_N];
int calc(int l, int r)
{
    int &res = dp[l][r];
    if (res != -1)
        return res;
    if (l > r)
        return res = 0;
    if (l == r)
        return res = 1;
    res = 1 + calc(l + 1, r);
    for (int i = l + 1; i <= r; i++)
        if (str[i] == str[l])
            res = min(res, calc(l + 1, i - 1) + calc(i, r));
    return res;
}
int main()
{
    memset(dp, -1, sizeof(dp));
    scanf("%d%s", &n, str + 1);
    printf("%d", calc(1, n));
    return 0;
}