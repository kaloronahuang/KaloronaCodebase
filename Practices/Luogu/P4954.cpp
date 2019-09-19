// P4954.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, wi[MAX_N], dp[MAX_N], g[MAX_N], q[MAX_N], head, tail;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]), wi[i] += wi[i - 1];
    // normally;
    head = 1, tail = 1, q[1] = n + 1;
    for (int i = n ;i >= 1;i--)
    {
        while (head < tail && dp[q[head + 1]] <= wi[q[head + 1] - 1] - wi[i - 1])
            head++;
        dp[i] = wi[q[head] - 1] - wi[i - 1];
        g[i] = g[q[head]] + 1;
        while (head < tail && dp[i] - wi[i - 1] < dp[q[tail]] - wi[q[tail] - 1])
            tail--;
        q[++tail] = i;
    }
    printf("%d", g[1]);
    return 0;
}