// POJ1180.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX_N = 10100;
int n, s, ti[MAX_N], ci[MAX_N], dp[MAX_N], sumc[MAX_N], sumt[MAX_N], q[MAX_N];
int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &ti[i], &ci[i]);
        sumt[i] = sumt[i - 1] + ti[i], sumc[i] = sumc[i - 1] + ci[i];
    }
    int head = 1, tail = 1;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && dp[q[head + 1]] - dp[q[head]] <= (s + sumt[i]) * (sumc[q[head + 1]] - sumc[q[head]]))
            head++;
        int j = q[head];
        dp[i] = dp[j] - s * sumc[j] - sumt[i] * sumc[j] + s * sumc[n] + sumt[i] * sumc[i];
        while (head < tail && double(dp[q[tail]] - dp[q[tail - 1]]) / double(sumc[q[tail]] - sumc[q[tail - 1]]) >= double(dp[i] - dp[q[tail]]) / double(sumc[i] - sumc[q[tail]]))
            tail--;
        q[++tail] = i;
    }
    printf("%d", dp[n]);
    return 0;
}