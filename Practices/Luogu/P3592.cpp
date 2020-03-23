// P3592.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 52, MAX_M = 4005;

int n, m, dp[MAX_N][MAX_N][MAX_M], cnt[MAX_N][MAX_M], suf[MAX_N][MAX_N][MAX_M], pre[MAX_N][MAX_N][MAX_M], pre_pos[MAX_N][MAX_N][MAX_M];
int ai[MAX_M], bi[MAX_M], ci[MAX_M], upper, ans[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

void findAns(int i, int j, int k)
{
    if (i > j)
        return;
    int val = pre[i][j][k], pos = pre_pos[i][j][val];
    ans[pos] = mp[val - 1];
    findAns(i, pos - 1, val), findAns(pos + 1, j, val);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &ai[i], &bi[i], &ci[i]), mp.push_back(ci[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end()), upper = mp.size();
    for (int i = 1; i <= m; i++)
        ci[i] = ripe(ci[i]);
    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for (int k = i; k <= j; k++)
                for (int l = 0; l <= upper; l++)
                    cnt[k][l] = 0;
            for (int k = 1; k <= m; k++)
                if (i <= ai[k] && bi[k] <= j)
                    for (int ptr = ai[k]; ptr <= bi[k]; ptr++)
                        cnt[ptr][ci[k]]++;
            for (int k = i; k <= j; k++)
                for (int ptr = upper; ptr >= 1; ptr--)
                    cnt[k][ptr] += cnt[k][ptr + 1];
            for (int k = upper; k >= 1; k--)
            {
                int max_ans = 0;
                for (int mid = i; mid <= j; mid++)
                {
                    int tmp = suf[i][mid - 1][k] + suf[mid + 1][j][k] + cnt[mid][k] * mp[k - 1];
                    if (tmp >= max_ans)
                        max_ans = tmp, pre_pos[i][j][k] = mid;
                }
                if (max_ans >= suf[i][j][k + 1])
                    suf[i][j][k] = max_ans, pre[i][j][k] = k;
                else
                    suf[i][j][k] = suf[i][j][k + 1], pre[i][j][k] = pre[i][j][k + 1];
            }
        }
    findAns(1, n, 1);
    printf("%d\n", suf[1][n][1]);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}