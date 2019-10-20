// P4158.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 2550;

int n, m, T, dp[55][55][55][2], dp2[MAX_N];
vector<pr> blocks[110];
char opt[55][55];

void processIt(int id)
{
    for (int i = 1, siz = blocks[id].size(); i <= siz; i++)
        for (int j = siz; j >= 1; j--)
        {
            dp[id][i][j][0] = max(dp[id][i - 1][j][0], dp[id][i - 1][j][1]);
            dp[id][i][j][1] = max(dp[id][i - 1][j - 1][0], dp[id][i - 1][j - 1][1]) + blocks[id][i - 1].second - blocks[id][i - 1].first + 1;
            if (i >= 2)
                dp[id][i][j][1] = max(dp[id][i][j][1], dp[id][i - 2][j][1] + blocks[id][i - 1].second - blocks[id][i - 1].first + 1);
        }
}

int main()
{
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt[i] + 1);
    for (int i = 1; i <= n; i++)
        // preprocess;
        for (int j = 1, last = 1; j <= m + 1; j++)
            if (opt[i][j] == opt[i][last])
                continue;
            else
                blocks[i].push_back(make_pair(last, j - 1)), last = j;
    for (int i = 1; i <= n; i++)
        processIt(i);
    for (int i = 1; i <= n; i++)
        for (int pack = T; pack >= 0; pack--)
            for (int subpack = 0, siz = blocks[i].size(); subpack <= min(pack, siz); subpack++)
                dp2[pack] = max(dp2[pack], dp2[pack - subpack] + max(dp[i][siz][subpack][0], dp[i][siz][subpack][1]));
    printf("%d", dp2[T]);
    return 0;
}