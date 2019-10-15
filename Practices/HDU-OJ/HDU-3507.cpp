// HDU-3507.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 500100;

ll n, m, dp[MAX_N], prefix[MAX_N];
int q[MAX_N], head, tail;

ll pow2(ll bas) { return bas * bas; }

ll slope1(int a, int b)
{
    return (dp[a] - dp[b]) + (pow2(prefix[a]) - pow2(prefix[b]));
}

ll slope2(int a, int b)
{
    return 2 * (prefix[a] - prefix[b]);
}

int main()
{
    while (scanf("%lld%lld", &n, &m) != EOF)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lld", &prefix[i]), prefix[i] += prefix[i - 1];
        head = tail = 1, q[1] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (head < tail && slope1(q[head + 1], q[head]) <= prefix[i] * slope2(q[head + 1], q[head]))
                head++;
            dp[i] = dp[q[head]] + pow2(prefix[i] - prefix[q[head]]) + m;
            while (head < tail && slope1(i, q[tail]) * slope2(q[tail], q[tail - 1]) <= slope1(q[tail], q[tail - 1]) * slope2(i, q[tail]))
                tail--;
            q[++tail] = i;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}