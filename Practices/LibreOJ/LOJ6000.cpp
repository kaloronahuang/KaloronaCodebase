// LOJ6000.cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> G[110];
int n, m, tmpx, tmpy, ans, dfn[110], match[110];
bool dfs(int u, int org)
{
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
    {
        int to = G[u][i];
        if (dfn[to] != org)
        {
            dfn[to] = org;
            if ((!match[to]) || dfs(match[to], org))
            {
                match[to] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    m = n - m, n = n - m;
    while (~scanf("%d%d", &tmpx, &tmpy))
        G[tmpx].push_back(tmpy);
    for (int i = 1; i <= n; i++)
        if (dfs(i, i))
            ans++;
    printf("%d", ans);
    return 0;
}