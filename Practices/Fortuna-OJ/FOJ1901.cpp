// FOJ1901.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7070;

int n, q, ans, dp[MAX_N][2];
pair<int, int> pts[MAX_N];

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second);
    sort(pts + 1, pts + 1 + n);
    for (int i = 1; i <= n; i++)
        for (int j = i - 1; j >= 1; j--)
            if (pts[i].second < pts[j].second)
                dp[j][1] = (0LL + dp[j][1] + dp[i][0] + 1) % q;
            else
                dp[i][0] = (0LL + dp[j][1] + dp[i][0] + 1) % q;
    for (int i = 1; i <= n; i++)
        ans = (0LL + ans + dp[i][0] + dp[i][1]) % q;
    ans = (0LL + ans + n) % q;
    printf("%d\n", ans);
    return 0;
}