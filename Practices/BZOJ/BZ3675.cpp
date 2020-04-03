// BZ3675.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_K = 220;

typedef long long ll;

int n, k, ai[MAX_N], q[MAX_N];
ll dp[MAX_N][2], pre[MAX_N];

long double pow2(ll bas) { return bas * bas; }

long double slope(int x, int y, int j) { return (long double)((dp[y][(j - 1) & 1] - pow2(pre[y])) - (dp[x][(j - 1) & 1] - pow2(pre[x]))) / (long double)(pre[y] - pre[x]); }

int main()
{
    scanf("%d%d", &n, &k);
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        if (ai[i] != 0)
            tot++, pre[tot] = pre[tot - 1] + ai[i];
    }
    n = tot;
    for (int j = 1; j <= k; j++)
    {
        int head = 1, tail = 1;
        q[1] = 0;
        for (int i = 0; i < MAX_N; i++)
            dp[i][j & 1] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (head < tail && slope(q[head], q[head + 1], j) > -pre[i])
                head++;
            dp[i][j & 1] = dp[q[head]][(j - 1) & 1] + 1LL * pre[q[head]] * (pre[i] - pre[q[head]]);
            while (head < tail && slope(q[tail - 1], q[tail], j) <= slope(q[tail], i, j))
                tail--;
            q[++tail] = i;
        }
    }
    printf("%lld\n", dp[n][k & 1]);
    return 0;
}