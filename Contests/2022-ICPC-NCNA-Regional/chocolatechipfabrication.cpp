// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAX_N = 2020;

int n, m, dep[MAX_N][MAX_N];
char mp[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];

int main()
{
    memset(dep, 0x3f, sizeof(dep));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    queue<pii> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == 'X')
            {
                bool flag = (mp[i - 1][j] == 'X' && mp[i][j - 1] == 'X' && mp[i + 1][j] == 'X' && mp[i][j + 1] == 'X');
                if (!flag)
                    dep[i][j] = 1, q.push(make_pair(i, j)), vis[i][j] = true;
            }
    while (!q.empty())
    {
        pii u = q.front();
        q.pop();
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};
        for (int d = 0; d < 4; d++)
        {
            int dstx = dx[d] + u.first;
            int dsty = dy[d] + u.second;
            if (dstx <= n && dstx >= 1 && dsty <= m && dsty >= 1 && mp[dstx][dsty] == 'X' && dep[dstx][dsty] > dep[u.first][u.second] + 1)
                dep[dstx][dsty] = dep[u.first][u.second] + 1, q.push(make_pair(dstx, dsty));
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j] == 'X')
                ans = max(ans, dep[i][j]);
    printf("%d\n", ans);
    return 0;
}