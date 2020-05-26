// P4563.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, hi[MAX_N], dp[MAX_N][MAX_N];
bool trans[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i - 1, last_pos = 0; j >= 1; j--)
            if (last_pos == 0 || 1LL * (hi[i] - hi[j]) * (i - last_pos) < 1LL * (hi[i] - hi[last_pos]) * (i - j))
                trans[j][i] = true, last_pos = j;
    int ans = 0;
    for (int r = 1; r <= n; r++)
        for (int l = r, pre = 1, last_pos = 0; l >= 1; l--)
        {
            if (trans[l][r])
            {
                if (!trans[l + 1][r])
                    pre += min(dp[l + 1][last_pos], dp[l + 1][last_pos + 1]);
                dp[l][r] = pre;
            }
            else
            {
                if (trans[l + 1][r])
                    last_pos = l;
                dp[l][r] = pre + min(dp[l][last_pos], dp[l][last_pos + 1]);
            }
            ans ^= dp[l][r];
        }
    printf("%d\n", ans);
    return 0;
}