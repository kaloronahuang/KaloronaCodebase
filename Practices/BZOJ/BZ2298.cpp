// BZ2298.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 101000;
int n, dp[MAX_N], cnt;
struct pr
{
    int first, second;
    bool operator<(const pr &p) const
    {
        return second < p.second || (second == p.second && first < p.first);
    }
} res[MAX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x + y < n)
            res[++cnt].first = x + 1, res[cnt].second = n - y;
    }
    sort(res + 1, res + 1 + cnt);
    int cur = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1];
        int tmp = 0;
        while (res[cur].second < i)
            cur++;
        for (; res[cur].second == i; cur++)
        {
            if (res[cur].first == res[cur - 1].first)
                tmp++;
            else
                tmp = 1;
            dp[i] = max(dp[i], dp[res[cur].first - 1] + min(tmp, i - res[cur].first + 1));
        }
    }
    printf("%d", n - dp[n]);
    return 0;
}