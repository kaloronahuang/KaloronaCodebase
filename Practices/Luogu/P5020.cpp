// P5020.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_DOM = 25010;

int T, n, ai[MAX_N];
bool dp[MAX_DOM];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        sort(ai + 1, ai + 1 + n);
        memset(dp, false, sizeof(dp)), dp[0] = true;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (dp[ai[i]] == true)
                continue;
            cnt++;
            for (int j = 0; j < MAX_DOM; j++)
                if (j >= ai[i])
                    dp[j] |= dp[j - ai[i]];
        }
        printf("%d\n", cnt);
    }
    return 0;
}