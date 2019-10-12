// P1441.cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, ai[22], answer;
bool vis[22], dp[2020];

void dfs(int pos, int cnt)
{
    if (pos == n + 1)
    {
        if (cnt > 0)
            return;
        // come to check;
        int cnt = 0;
        memset(dp, 0, sizeof(dp)), dp[0] = true;
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                for (int j = 2000; j >= ai[i]; j--)
                {
                    if (dp[j] == false && dp[j - ai[i]] == true)
                        cnt++;
                    dp[j] |= dp[j - ai[i]];
                }
        answer = max(answer, cnt);
        return;
    }
    dfs(pos + 1, cnt);
    if (cnt > 0)
        vis[pos] = true, dfs(pos + 1, cnt - 1), vis[pos] = false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    dfs(1, m), printf("%d", answer);
    return 0;
}