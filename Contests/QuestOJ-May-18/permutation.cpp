// permutation.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, ai[MAX_N], deg[MAX_N];
bool vis[MAX_N];

bool dfs(int u)
{
    if (vis[u])
        return false;
    vis[u] = true;
    return ai[u] ? !dfs(ai[u]) : 0;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        if (ai[i] != 0)
            deg[ai[i]] = 1;
    }
    if (n & 1)
        puts("0"), exit(0);
    int x = 0, y = 0;
    for (int i = 1, tmp; i <= n; i++)
        if (!deg[i])
            tmp = dfs(i), y += tmp, x += !tmp;
    for (int i = 1; i <= n; i++)
        if (!vis[i] && dfs(i))
            puts("0"), exit(0);
    int ans = 1;
    for (int i = 1; i <= x; i += 2)
        ans = 1LL * ans * i % mod;
    ans = 1LL * ans * ans % mod;
    for (int i = x + 1; i <= x + y; i++)
        ans = 1LL * ans * i % mod;
    printf("%d\n", ans);
    return 0;
}