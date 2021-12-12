// square.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e3 + 200;

int n, pre[MAX_N][MAX_N];
char mp[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + (mp[i][j] == '1');
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j] == '1')
            {
                int l = 1, r = min(i, j), pans = 1;
                while (l <= r)
                {
                    int mid = (l + r) >> 1;
                    if (pre[i][j] - pre[i - mid][j] - pre[i][j - mid] + pre[i - mid][j - mid] == 1LL * mid * mid)
                        pans = mid, l = mid + 1;
                    else
                        r = mid - 1;
                }
                ans += pans;
            }
    printf("%lld\n", ans);
    return 0;
}