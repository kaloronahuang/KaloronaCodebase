// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int n, dist[MAX_N][MAX_N], col[MAX_N];
char mp[MAX_N][MAX_N];

bool dfs(int u, int c)
{
    if (col[u] != -1 && c != col[u])
        return false;
    else if (col[u] != -1)
        return true;
    col[u] = c;
    for (int v = 1; v <= n; v++)
        if (mp[u][v] != '0' && !dfs(v, c ^ 1))
            return false;
    return true;
}

int main()
{
    memset(col, -1, sizeof(col));
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        if (col[i] == -1 && !dfs(i, 0))
            puts("-1"), exit(0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j] == '1')
                dist[i][j] = 1;
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    int answer = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            answer = max(answer, dist[i][j]);
    printf("%d\n", answer + 1);
    return 0;
}