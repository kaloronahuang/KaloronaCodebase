// P5202.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, limit, prefix[MAX_N], q[MAX_N], head, tail, dp[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%d%d%s", &n, &limit, str + 1);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + (str[i] == 'H' ? 1 : -1);
    head = 1, tail = 0, q[++tail] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head <= tail && i - q[head] > limit)
            head++;
        dp[i] = dp[q[head]] + (prefix[i] - prefix[q[head]] <= 0);
        while (head <= tail && (dp[i] < dp[q[tail]] || (dp[i] == dp[q[tail]] && prefix[i] < prefix[q[tail]])))
            tail--;
        q[++tail] = i;
    }
    printf("%d\n", dp[n]);
    return 0;
}