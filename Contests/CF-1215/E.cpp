// E.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 4e5 + 200, MAX_C = 21;

int n;
ll swap_cost[MAX_C][MAX_C], dp[1 << MAX_C];
vector<int> col_pos[MAX_C];

int main()
{
    scanf("%d", &n);
    for (int i = 0, tmp; i < n; i++)
        scanf("%d", &tmp), col_pos[--tmp].push_back(i);
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            if (i == j || col_pos[i].size() == 0 || col_pos[j].size() == 0)
                continue;
            int pos2 = 0;
            for (int pos1 = 0, siz = col_pos[i].size(); pos1 < siz; pos1++)
            {
                while (pos2 != col_pos[j].size() - 1 && col_pos[j][pos2 + 1] <= col_pos[i][pos1])
                    pos2++;
                if (col_pos[i][pos1] > col_pos[j][pos2])
                    swap_cost[i][j] += pos2 + 1;
            }
        }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int mask = 0; mask < (1 << 20); mask++)
    {
        vector<int> colors;
        for (int i = 0; i < 20; i++)
            if (mask & (1 << i))
                colors.push_back(i);
        for (int i = 0; i < 20; i++)
            if ((mask & (1 << i)) == 0)
            {
                long long stat = 0;
                for (int j = 0, siz = colors.size(); j < siz; j++)
                    stat += swap_cost[colors[j]][i];
                dp[mask | (1 << i)] = min(dp[mask | (1 << i)], dp[mask] + stat);
            }
    }
    printf("%lld", dp[(1 << 20) - 1]);
    return 0;
}