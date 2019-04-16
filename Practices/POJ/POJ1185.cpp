// POJ1185.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110, RANGE = 1 << 10;
int n, m, dp[MAX_N][RANGE], terrian[MAX_N];
int dfs(int curt, int stat)
{
    int &ans = dp[curt][stat];
    if(curt == 0)
        return ans = 0;
    if (ans != -1)
        return ans;
    ans = 0;
    for (int i = 0; i < m; i++)
    {
        int curtBit = (stat >> (i << 1)) & 3;
        if (curtBit == 2 && ((terrian[curt] >> i) & 1) != 1)
            return (ans = 0);
    }
    for (int prev_stat = 0; prev_stat < (1 << (m << 1)); prev_stat++)
    {
        int cnt = 0;
        bool flag = true;
        for (int i = 0; i < m; i++)
        {
            int curtBit = (stat >> (i << 1)) & 3, prevBit = (prev_stat >> (i << 1)) & 3;
            if(curtBit == 2 && prevBit != 0)
            {
                flag = false;
                break;
            }
            if(curtBit == 1 && prevBit != 2)
            {
                flag = false;
                break;
            }
            if(curtBit == 0 && prevBit == 2)
            {
                flag = false;
                break;
            }
            if (curtBit == 2)
                cnt++;
        }
        if (!flag)
            continue;
        ans = max(ans, dfs(curt - 1, prev_stat) + cnt);
    }
    return ans;
}
int main()
{
    // input;
    memset(dp, -1, sizeof(dp));
    scanf("%d%d", &n, &m);
    terrian[0] = (1 << m) - 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
        {
            char ch;
            scanf("%c", &ch);
            if (ch == 'P')
                terrian[i] |= (1 << j);
        }
    int ans = 0;
    for (int i = 0; i < (1 << (n << 1)); i++)
        ans = max(ans, dfs(n, i));
    printf("%d", ans);
    return 0;
}