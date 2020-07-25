// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

typedef pair<int, int> pii;

int n, m, dist[MAX_N][MAX_N];
char S[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", S[i] + 1);
    memset(dist, 0x3f, sizeof(dist));
    queue<pii> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (S[i][j] == '#')
                dist[i][j] = 0, q.push(make_pair(i, j));
    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            int dstx = x + dx[d], dsty = y + dy[d];
            if (S[dstx][dsty] != '\0' && dist[dstx][dsty] > dist[x][y] + 1)
                dist[dstx][dsty] = dist[x][y] + 1, q.push(make_pair(dstx, dsty));
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = max(ans, dist[i][j]);
    printf("%d\n", ans);
    return 0;
}