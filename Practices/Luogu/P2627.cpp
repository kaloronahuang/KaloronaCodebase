// P2627.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll dp[MAX_N], n, k, seq[MAX_N], prefix[MAX_N];
int q[MAX_N], head, tail;

int main()
{
    scanf("%lld%lld", &n, &k), n++;
    for (int i = 2; i <= n; i++)
        scanf("%lld", &seq[i]), prefix[i] = prefix[i - 1] + seq[i];
    head = tail = 1, q[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1];
        while (head <= tail && i - q[head] > k)
            head++;
        dp[i] = max(dp[i], dp[q[head] - 1] + prefix[i] - prefix[q[head]]);
        while (head <= tail && dp[i - 1] - prefix[i] > dp[q[tail] - 1] - prefix[q[tail]])
            tail--;
        q[++tail] = i;
    }
    printf("%lld", dp[n]);
    return 0;
}