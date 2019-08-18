// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 220;

int perm[MAX_N], T, n, m, matching[MAX_N], dfn[MAX_N];
bool vis[MAX_N][MAX_N];
char str1[MAX_N], str2[MAX_N];

bool dfs(int u)
{
    for (int i = 1; i <= m; i++)
    {
        if (!vis[u][i])
            continue;
        if (!dfn[i])
        {
            dfn[i] = u;

            if ((!matching[i]) || dfs(matching[i]))
            {
                matching[i] = u;
                perm[u] = i;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(vis, 0, sizeof(vis));
        memset(matching, 0, sizeof(matching)), memset(dfn, 0, sizeof(dfn));
        memset(perm, 0, sizeof(perm));

        scanf("%d%d", &n, &m);
        // initial;
        scanf("%s%s", str1 + 1, str2 + 1);
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                if (str1[i] == str2[j])
                    vis[i][j] = true;
        for (int curt_case = 2; curt_case <= n; curt_case++)
        {
            scanf("%s%s", str1 + 1, str2 + 1);
            for (int i = 1; i <= m; i++)
                for (int j = 1; j <= m; j++)
                    if (str1[i] == str2[j])
                        vis[i][j] &= true;
                    else if (str1[i] != str2[j])
                        vis[i][j] = false;
        }

        for (int i = 1; i <= m; i++)
        {
            memset(matching, 0, sizeof(matching));
            if (!dfs(i))
            {
                puts("-1");
                goto getout;
            }
        }

        for (int i = 1; i < m; i++)
            printf("%d ", perm[i]);
        printf("%d\n", perm[m]);

    getout:
        continue;
    }
    return 0;
}
