// ARC092D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_E = 2e5 + 200;

int n, m, mp[MAX_N][MAX_N], etot, ui[MAX_E], vi[MAX_E], p[MAX_N], q[MAX_N];
bool accessible[MAX_N][MAX_N], vis[MAX_N], enabled[MAX_N][MAX_N];
vector<int> G[MAX_N];

void mark(int u, int root)
{
    vis[u] = true, accessible[root][u] = true;
    for (int v : G[u])
        if (!vis[v])
            mark(v, root);
}

void markPos(int u)
{
    vis[u] = true;
    for (int v : G[u])
        if (!vis[v])
            p[v] = mp[u][v], markPos(v);
}

void markNeg(int u)
{
    vis[u] = true;
    int siz = G[u].size() - 1;
    for (int i = siz; i >= 0; i--)
    {
        int v = G[u][i];
        if (!vis[v])
            q[v] = mp[u][v], markNeg(v);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        ui[++etot] = u, vi[etot] = v;
        mp[u][v] = etot, G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        mark(i, i), memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
    {
        markPos(i), memset(vis, false, sizeof(vis));
        markNeg(i), memset(vis, false, sizeof(vis));
        for (int v : G[i])
            if (p[v] != mp[i][v] || q[v] != mp[i][v])
                enabled[i][v] = true;
        memset(p, 0, sizeof(p)), memset(q, 0, sizeof(q));
    }
    for (int i = 1; i <= m; i++)
        puts((accessible[vi[i]][ui[i]] ^ enabled[ui[i]][vi[i]]) ? "diff" : "same");
    return 0;
}