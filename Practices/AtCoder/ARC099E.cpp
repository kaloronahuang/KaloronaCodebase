// ARC099E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 770;

int n, m, color[MAX_N], cnt[2];
bool G[MAX_N][MAX_N], tmp[MAX_N << 1], pack[MAX_N << 1];

void dfs(int u, int col)
{
    color[u] = col, cnt[col == 1]++;
    for (int i = 1; i <= n; i++)
        if (G[u][i] == false && i != u)
            if (color[i] == col)
                puts("-1"), exit(0);
            else if (color[i] == 0)
                dfs(i, -col);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u][v] = G[v][u] = true;
    pack[0] = true;
    for (int i = 1; i <= n; i++)
        if (!color[i])
        {
            cnt[0] = cnt[1] = 0, dfs(i, 1);
            memset(tmp, false, sizeof(tmp));
            for (int j = 0; j <= n; j++)
                tmp[j + cnt[0]] |= pack[j], tmp[j + cnt[1]] |= pack[j];
            memcpy(pack, tmp, sizeof(pack));
        }
    int ans = 0x7fffffff;
    for (int i = 0; i <= n; i++)
        if (pack[i])
            ans = min(ans, i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2);
    printf("%d\n", ans);
    return 0;
}