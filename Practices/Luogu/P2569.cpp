// P2569.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2020;

int T, maxP, w, ap[MAX_N], bp[MAX_N], as[MAX_N], bs[MAX_N], q[MAX_N << 3];
int dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d", &T, &maxP, &w);
    for (int i = 1; i <= T; i++)
        scanf("%d%d%d%d", &ap[i], &bp[i], &as[i], &bs[i]);
    memset(dp, -0x3f, sizeof(dp));
    for (int day = 1; day <= T; day++)
    {
        for (int stock = 0; stock <= as[day]; stock++)
            dp[day][stock] = -1 * stock * ap[day];
        for (int stock = 0; stock <= maxP; stock++)
            dp[day][stock] = max(dp[day][stock], dp[day - 1][stock]);
        if (day <= w)
            continue;
        int head = 1, tail = 0;
        for (int stock = 0; stock <= maxP; stock++)
        {
            while (head <= tail && q[head] < stock - as[day])
                head++;
            while (head <= tail && dp[day - w - 1][q[tail]] + q[tail] * ap[day] <= dp[day - w - 1][stock] + stock * ap[day])
                tail--;
            q[++tail] = stock;
            if (head <= tail)
                dp[day][stock] = max(dp[day][stock], dp[day - w - 1][q[head]] - (stock - q[head]) * ap[day]);
        }
        head = 1, tail = 0;
        for (int stock = maxP; stock >= 0; stock--)
        {
            while (head <= tail && q[head] > stock + bs[day])
                head++;
            while (head <= tail && dp[day - w - 1][q[tail]] + q[tail] * bp[day] <= dp[day - w - 1][stock] + stock * bp[day])
                tail--;
            q[++tail] = stock;
            if (head <= tail)
                dp[day][stock] = max(dp[day][stock], dp[day - w - 1][q[head]] + (q[head] - stock) * bp[day]);
        }
    }
    int ans = -0x3f3f3f3f;
    for (int i = 0; i <= maxP; i++)
        ans = max(dp[T][i], ans);
    printf("%d", ans);
    return 0;
}