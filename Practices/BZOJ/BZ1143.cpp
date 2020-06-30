// P4298.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_E = 1010;

int n, m, matching[MAX_N], vis[MAX_N];
bool mp[MAX_N][MAX_N];

bool hungary(int u, int org)
{
    for (int v = 1; v <= n; v++)
        if (vis[v] != org && mp[u][v])
        {
            vis[v] = org;
            if (matching[v] == 0 || hungary(matching[v], org))
            {
                matching[v] = u;
                return true;
            }
        }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), mp[u][v] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mp[i][j] |= mp[i][k] && mp[k][j];
    int ans = n;
    for (int i = 1; i <= n; i++)
        if (hungary(i, i))
            ans--;
    printf("%d\n", ans);
    return 0;
}