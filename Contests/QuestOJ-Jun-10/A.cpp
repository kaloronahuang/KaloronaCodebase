// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, k, siz[MAX_N];
vector<int> G[MAX_N];
bool flag;

void dfs(int u, int fa)
{
    siz[u] = 1;
    int leaf = 0;
    for (int v : G[u])
        if (v != fa)
        {
            dfs(v, u), siz[u] += siz[v];
            if (siz[v] == 1)
                leaf++;
        }
    if (leaf >= 2)
        flag = true;
}

void cut(int u, int fa)
{
    siz[u] = 1;
    for (int v : G[u])
        if (v != fa)
        {
            cut(v, u);
            if (siz[v] == 2)
                siz[v] = 0, k--;
            siz[u] += siz[v];
        }
    if (siz[u] > 2)
        flag = true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &k), flag = false;
        for (int i = 1; i <= n; i++)
            G[i].clear(), siz[i] = 0;
        for (int i = 1, u, v; i <= n - 1; i++)
            scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
        if (n % 2 == 1)
        {
            puts("Alice");
            continue;
        }
        if (n == 2)
        {
            puts("Bob");
            continue;
        }
        dfs(1, 0), cut(1, 0);
        if (flag || k < 0 || siz[1] != 2)
            puts("Alice");
        else
            puts("Bob");
    }
    return 0;
}