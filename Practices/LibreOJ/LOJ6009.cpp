// LOJ6009.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21, MAX_M = 110;

int n, m, b[MAX_M][2], f[MAX_M][2], ti[MAX_M], dist[1 << MAX_N];
bool vis[1 << MAX_N];
char str[2][MAX_M];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%s%s", &ti[i], str[0], str[1]);
        for (int j = 0; j < n; j++)
            if (str[0][j] == '+')
                b[i][0] |= (1 << j);
            else if (str[0][j] == '-')
                b[i][1] |= (1 << j);
        for (int j = 0; j < n; j++)
            if (str[1][j] == '-')
                f[i][0] |= (1 << j);
            else if (str[1][j] == '+')
                f[i][1] |= (1 << j);
    }
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push((1 << n) - 1), vis[(1 << n) - 1] = true;
    dist[(1 << n) - 1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = 1; i <= m; i++)
            if (((u & b[i][0]) == b[i][0]) && ((u & b[i][1]) == 0))
            {
                int nxtStat = (u ^ (u & f[i][0])) | f[i][1];
                if (dist[u] + ti[i] < dist[nxtStat])
                {
                    dist[nxtStat] = dist[u] + ti[i];
                    if (vis[nxtStat] == false)
                        vis[nxtStat] = true, q.push(nxtStat);
                }
            }
    }
    printf("%d\n", dist[0] == 0x3f3f3f3f ? 0 : dist[0]);
    return 0;
}