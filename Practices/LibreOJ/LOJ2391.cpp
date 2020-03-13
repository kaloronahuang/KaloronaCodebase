// LOJ2391.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, ai[MAX_N], bi[MAX_N], id[MAX_N << 1], nxt[MAX_N], fa[MAX_N], aff[MAX_N], atot, anti[MAX_N], color[MAX_N];
vector<int> G[MAX_N];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void addpath(int u, int v) { G[u].push_back(v), G[v].push_back(u); }

bool dfs(int u)
{
    for (auto x : G[u])
    {
        if (color[x] != -1 && color[x] == color[u])
            return false;
        if (color[x] == -1)
        {
            color[x] = color[u] ^ 1;
            if (!dfs(x))
                return false;
        }
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]), id[ai[i]] = id[bi[i]] = i, nxt[i] = fa[i] = i;
    fa[n + 1] = n + 1;
    for (int i = 1; i <= (n << 1); i++)
    {
        int p = id[i];
        if (!anti[p])
            aff[++atot] = p, anti[p] = atot;
        else
        {
            int u = anti[p];
            fa[u] = find(u + 1);
            for (int j = fa[u], ptr; j <= atot; j = ptr)
                addpath(aff[j], p), ptr = find(nxt[j] + 1), nxt[j] = atot;
        }
    }
    memset(color, -1, sizeof(color));
    int ans = 1;
    for (int i = 1; i <= n; i++)
        if (color[i] == -1)
        {
            color[i] = 0;
            if (dfs(i))
                ans = 2LL * ans % mod;
            else
                puts("0"), exit(0);
        }
    printf("%d\n", ans);
    return 0;
}