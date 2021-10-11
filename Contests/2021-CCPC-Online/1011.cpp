// 1011.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, ai[MAX_N], ufs[MAX_N], head[MAX_N], current, idx[MAX_N], dep[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return x == ufs[x] ? x : ufs[x] = find(ufs[x]); }

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to, u);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            head[i] = -1, G[i].clear();
        current = 0;
        for (int i = 1, u, v; i <= n - 1; i++)
            scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1; i <= n; i++)
            idx[i] = ufs[i] = i;
        sort(idx + 1, idx + 1 + n, [](const int &lhs, const int &rhs)
             { return ai[lhs] < ai[rhs]; });
        for (int id = 1; id <= n; id++)
        {
            int u = idx[id];
            for (int v : G[u])
                if (ai[v] < ai[u])
                {
                    int fv = find(v);
                    ufs[fv] = u;
                    addpath(u, fv);
                }
        }
        int root = idx[n];
        dfs(root, 0);
        for (int i = 1; i <= n; i++)
            printf("%d\n", dep[i]);
    }
    return 0;
}