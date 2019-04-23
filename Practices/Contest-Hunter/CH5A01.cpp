// CH5A01.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5050;
int n, s, ti[MAX_N], ci[MAX_N], dp[MAX_N], sumc[MAX_N], sumt[MAX_N];
int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &ti[i], &ci[i]);
        sumt[i] = sumt[i - 1] + ti[i], sumc[i] = sumc[i - 1] + ci[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            dp[i] = min(dp[i], dp[j] + sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]));
    printf("%d", dp[n]);
    return 0;
}