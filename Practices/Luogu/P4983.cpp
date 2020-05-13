// P4983.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
const long double bas = 1.0;

typedef long long ll;

int n, m, q[MAX_N];
ll pre[MAX_N], dp[MAX_N], seg[MAX_N], Xi[MAX_N], Yi[MAX_N];

ll slope1(int x, int y) { return (Yi[y] - Yi[x]); }

ll slope2(int x, int y) { return (Xi[y] - Xi[x]); }

int check(ll bias)
{
    int head = 1, tail = 0;
    q[++tail] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && bas * slope1(q[head], q[head + 1]) <= bas * 2LL * pre[i] * slope2(q[head], q[head + 1]))
            head++;
        dp[i] = Yi[q[head]] - 2LL * pre[i] * Xi[q[head]] + 1LL * pre[i] * pre[i] + 2LL * pre[i] + 1 + bias;
        Xi[i] = pre[i], Yi[i] = 1LL * pre[i] * pre[i] - 2LL * pre[i] + dp[i], seg[i] = seg[q[head]] + 1;
        while (head < tail && bas * 1LL * slope1(q[tail - 1], q[tail]) * slope2(q[tail - 1], i) >= bas * 1LL * slope1(q[tail - 1], i) * slope2(q[tail - 1], q[tail]))
            tail--;
        q[++tail] = i;
    }
    return seg[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &pre[i]), pre[i] += pre[i - 1];
    ll l = -1e18, r = 1e18, res = 0;
    while (l <= r)
    {
        ll mid = (l + r) / 2LL;
        if (check(mid) >= m)
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    check(res), printf("%lld\n", dp[n] - 1LL * m * res);
    return 0;
}