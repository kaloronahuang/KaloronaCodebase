// P5017.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 4e6 + 200;

int prefix[MAX_N], n, m, upper, q[MAX_N], head, tail;
ll tim[MAX_N], dp[MAX_N];

double judge(int a, int b) { return double((tim[b] + dp[b]) - (tim[a] + dp[a])) / double(prefix[b] - prefix[a] == 0 ? 1e-9 : (prefix[b] - prefix[a])); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, ti; i <= n; i++)
        scanf("%d", &ti), prefix[ti]++, tim[ti] += ti, upper = max(upper, ti);
    upper += m;
    for (int i = 1; i <= upper; i++)
        prefix[i] += prefix[i - 1], tim[i] += tim[i - 1];
    head = 1;
    for (int T = 0; T < upper; T++)
    {
        if (T >= m)
        {
            while (head < tail && judge(q[tail - 1], q[tail]) >= judge(q[tail], T - m))
                tail--;
            q[++tail] = T - m;
        }
        while (head < tail && judge(q[head], q[head + 1]) <= T)
            head++;
        dp[T] = prefix[T] * T - tim[T];
        if (head <= tail)
            dp[T] = min(dp[T], dp[T] = dp[q[head]] + 1LL * (prefix[T] - prefix[q[head]]) * T - (tim[T] - tim[q[head]]));
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = upper - m; i < upper; i++)
        ans = min(ans, dp[i]);
    printf("%lld", ans);
    return 0;
}