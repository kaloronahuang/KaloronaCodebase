// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 201000;

int dp[MAX_N], lft[MAX_N], rig[MAX_N], n, m, q[MAX_N << 1];

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n + 1; i++)
        rig[i] = i - 1;

    for (int i = 1, l, r; i <= m; i++)
        scanf("%d%d", &l, &r), rig[r] = min(rig[r], l - 1), lft[r + 1] = max(lft[r + 1], l);
    for (int i = n; i >= 1; i--)
        rig[i] = min(rig[i], rig[i + 1]);
    for (int i = 2; i <= n + 1; i++)
        lft[i] = max(lft[i], lft[i - 1]);
    int l = 1, r = 1, j = 1;
    q[1] = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        while (j <= min(rig[i], n))
        {
            if (dp[j] == -1)
            {
                j++;
                continue;
            }
            while (l <= r && dp[j] > dp[q[r]])
                r--;
            q[++r] = j, j++;
        }
        while (l <= r && q[l] < lft[i])
            l++;
        if (l <= r)
            dp[i] = dp[q[l]] + ((i != n + 1) ? 1 : 0);
        else
            dp[i] = -1;
    }
    printf("%d", dp[n + 1]);
    return 0;
}