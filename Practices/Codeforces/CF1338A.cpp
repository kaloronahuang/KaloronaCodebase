// CF1338A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, ai[MAX_N], cost[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), ai[0] = -2e9;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), cost[i] = max(ai[i - 1], ai[i]) - ai[i], ai[i] = max(ai[i - 1], ai[i]);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 30; j >= 0; j--)
                if (cost[i] & (1 << j))
                {
                    ans = max(ans, j + 1);
                    break;
                }
        printf("%d\n", ans);
    }
    return 0;
}