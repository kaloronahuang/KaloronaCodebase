// CF311B.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAX_N = 200005;
ll n, m, p, di[MAX_N], key[MAX_N], tmpx, tmpy, q[MAX_N], dp[110][MAX_N], sum[MAX_N];
int main()
{
    scanf("%lld%lld%lld", &n, &m, &p);
    for (int i = 2; i <= n; i++)
        scanf("%lld", &di[i]), di[i] += di[i - 1];
    for (int i = 1; i <= m; i++)
        scanf("%lld%lld", &tmpx, &tmpy), key[i] = tmpy - di[tmpx], sum[i] = sum[i - 1] + key[i];
    sort(key + 1, key + 1 + m), memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= p; i++)
    {
        int head = 1, tail = 1;
        q[1] = 0;
        for (int j = 1; j <= m; j++)
        {
            while (head < tail && (dp[i - 1][q[head + 1]] + sum[q[head + 1]]) - (dp[i - 1][q[head]] + sum[q[head]]) <= key[j] * (q[head + 1] - q[head]))
                head++;
            int k = q[head];
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][k] + (j - k) * key[j] - sum[j] + sum[k]);
            while (head < tail && ((dp[i - 1][q[tail]] + sum[q[tail]]) - (dp[i - 1][q[tail - 1]] + sum[q[tail - 1]])) * (j - q[tail]) >= ((dp[i - 1][j] + sum[j]) - (dp[i - 1][q[tail]] + sum[q[tail]])) * (q[tail] - q[tail - 1]))
                tail--;
            q[++tail] = j;
        }
    }
    printf("%lld", dp[p][m]);
    return 0;
}