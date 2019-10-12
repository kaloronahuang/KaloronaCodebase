// P1341.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 330;
int G[MAX_N][MAX_N], deg[MAX_N], n;
char opt[2], ans[MAX_N * MAX_N];

void dfs(int u)
{
    for (int i = 0; i < MAX_N; i++)
        if (G[u][i] > 0)
            G[u][i] = G[i][u] = 0, dfs(i);
    ans[n--] = u;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", opt), G[opt[0]][opt[1]] = G[opt[1]][opt[0]] = true;
        deg[opt[0]]++, deg[opt[1]]++;
    }
    int pt = 0, cnt = 0;
    for (int i = 0; i < MAX_N; i++)
        if (deg[i] & 1)
        {
            cnt++;
            if (pt == 0)
                pt = i;
        }
    if (pt == 0)
        for (int i = 0; i < MAX_N; i++)
            if (deg[i] > 0)
            {
                pt = i;
                break;
            }
    if (cnt > 0 && cnt != 2)
        puts("No Solution"), exit(0);
    dfs(pt), puts(ans);
    return 0;
}