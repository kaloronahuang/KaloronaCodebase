// P3584.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000100;

int n, ai[MAX_N], dp[MAX_N][4], ans[MAX_N];

void transfer(int pre, int curt)
{
    if (dp[pre][2] != -1 && ai[pre] >= ai[curt])
        dp[curt][0] = 2;
    else if (dp[pre][3] != -1 && ai[pre] >= 2LL * ai[curt])
        dp[curt][0] = 3;

    if (dp[pre][0] != -1 && ai[pre] <= ai[curt])
        dp[curt][1] = 0;
    else if (dp[pre][1] != -1 && ai[pre] <= 2LL * ai[curt])
        dp[curt][1] = 1;

    if (dp[pre][2] != -1 && 2LL * ai[pre] >= ai[curt])
        dp[curt][2] = 2;
    else if (dp[pre][3] != -1 && ai[pre] >= ai[curt])
        dp[curt][2] = 3;

    if (dp[pre][0] != -1 && ai[pre] * 2 <= ai[curt])
        dp[curt][3] = 0;
    else if (dp[pre][1] != -1 && ai[pre] <= ai[curt])
        dp[curt][3] = 1;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int init_stat = 0; init_stat < 4; init_stat++)
    {
        memset(dp, -1, sizeof(dp)), dp[1][init_stat] = 4;
        for (int i = 2; i <= n; i++)
            transfer(i - 1, i);
        transfer(n, 1);
        if (dp[1][init_stat] != 4)
        {
            int nxt = dp[1][init_stat];
            for (int i = n; i >= 1; i--)
            {
                if (nxt == 1 || nxt == 3)
                    ans[(i - 2 + n) % n + 1] = i;
                if (nxt == 2 || nxt == 3)
                    ans[i] = i;
                nxt = dp[i][nxt];
            }
            for (int i = 1; i <= n; i++)
                printf("%d ", ans[i]);
            puts(""), exit(0);
        }
    }
    puts("NIE");
    return 0;
}