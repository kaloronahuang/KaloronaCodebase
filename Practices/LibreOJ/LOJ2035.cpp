// LOJ2035.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 3030;

int n, m, pre[MAX_N], q[MAX_N];
ll dp[2][MAX_N];

double pow2(double x) { return x * x; }

double slope(int a, int b, int i) { return double(1.0 * dp[i & 1][a] - dp[i & 1][b] + pow2(pre[a]) - pow2(pre[b])) / double(2.0 * (pre[a] - pre[b])); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pre[i]), pre[i] += pre[i - 1];
    for (int i = 1; i <= n; i++)
        dp[0][i] = 0x3f3f3f3f3f3f3f3f;
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++)
    {
        int head = 1, tail = 0;
        q[++tail] = 0;
        for (int j = 1; j <= n; j++)
        {
            while (head < tail && slope(q[head], q[head + 1], i - 1) < pre[j])
                head++;
            dp[i & 1][j] = dp[(i - 1) & 1][q[head]] + 1LL * (pre[j] - pre[q[head]]) * (pre[j] - pre[q[head]]);
            while (head < tail && slope(q[tail], q[tail - 1], i - 1) > slope(q[tail], j, i - 1))
                tail--;
            q[++tail] = j;
        }
    }
    printf("%lld\n", 1LL * dp[m & 1][n] * m - 1LL * pre[n] * pre[n]);
    return 0;
}