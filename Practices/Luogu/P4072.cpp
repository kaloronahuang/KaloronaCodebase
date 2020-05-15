// P4072.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

typedef long long ll;

int n, m, pre[MAX_N], q[MAX_N];
ll dp[MAX_N][MAX_N];

ll pow2(ll bas) { return bas * bas; }

ll X(int x) { return pre[x]; }

ll Y(int id, int x) { return dp[id][x] + pow2(pre[x]); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pre[i]), pre[i] += pre[i - 1];
    memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
    for (int i = 1; i <= m; i++)
    {
        int head = 1, tail = 0;
        q[++tail] = 0;
        for (int j = 1; j <= n; j++)
        {
            while (head < tail && Y(i - 1, q[head + 1]) - Y(i - 1, q[head]) < 2LL * pre[j] * (X(q[head + 1]) - X(q[head])))
                head++;
            dp[i][j] = dp[i - 1][q[head]] + pow2(pre[j] - pre[q[head]]);
            while (head < tail && (Y(i - 1, q[tail]) - Y(i - 1, q[tail - 1])) * (X(j) - X(q[tail - 1])) > (Y(i - 1, j) - Y(i - 1, q[tail - 1])) * (X(q[tail]) - X(q[tail - 1])))
                tail--;
            q[++tail] = j;
        }
    }
    printf("%lld\n", 1LL * m * dp[m][n] - pow2(pre[n]));
    return 0;
}