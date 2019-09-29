// F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500500;

int n, m, dfn[MAX_N], level[MAX_N], low[MAX_N];
vector<int> G[MAX_N];

void dfs(int v, int l = 0)
{
    dfn[v] = 1, level[v] = l;
    low[l] = v;
    int pt = -1;
    for (int i = 0, siz = G[v].size(); i < siz; i++)
    {
        int to = G[v][i];
        if (dfn[to] == 1 && (pt == -1 || level[pt] < level[to]))
            pt = to;
    }

    if (pt != -1)
    {
        set<int> ret;
        ret.insert(pt);
        for (int i = l; low[i] != pt; i--)
            ret.insert(low[i]);
        int cnt = 0;
        for (int u : ret)
            for (int to : G[u])
                if (ret.count(to))
                    cnt++;

        if (cnt == ret.size())
        {
            cout << cnt << endl;
            for (int u : ret)
                cout << u << endl;
            exit(0);
        }
    }

    for (int i = 0, siz = G[v].size(); i < siz; i++)
    {
        int to = G[v][i];
        if (dfn[to] == 0)
            dfs(to, l + 1);
    }
    dfn[v] = 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v);
    for (int i = 1; i <= n; i++)
        dfs(i, 0);
    puts("-1");
    return 0;
}