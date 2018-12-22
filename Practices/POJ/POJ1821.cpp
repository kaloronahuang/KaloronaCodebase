// POJ1821.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int MX_N = 16020;
int n, k, dp[120][MX_N];
struct worker
{
    int l, p, s;
    bool operator<(const worker &wk)
    {
        return s < wk.s;
    }
} wks[MX_N];
int calc(int i, int k)
{
    return dp[i - 1][k] - wks[i].p * k;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++)
        scanf("%d%d%d", &wks[i].l, &wks[i].p, &wks[i].s);
    sort(wks + 1, wks + 1 + k);
    for (int i = 1; i <= k; i++)
    {
        deque<int> q;
        for (int j = max(0, wks[i].s - wks[i].l); j <= wks[i].s - 1; j++)
        {
            while (!q.empty() && calc(i, q.back()) <= calc(i, j))
                q.pop_back();
            q.push_back(j);
        }
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (j >= wks[i].s)
            {
                while (!q.empty() && q.front() < j - wks[i].l)
                    q.pop_front();
                if (!q.empty())
                    dp[i][j] = max(dp[i][j], calc(i, q.front()) + wks[i].p * j);
            }
        }
    }
    printf("%d", dp[k][n]);
    return 0;
}