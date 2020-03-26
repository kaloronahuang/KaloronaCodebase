// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef pair<int, int> pii;

int n, m, q, sumx[MAX_N], sumy[MAX_N], color[MAX_N];
pii pts[MAX_N];
vector<int> G[MAX_N];

void dfs(int u, int org)
{
    color[u] = org;
    for (auto v : G[u])
        if (color[v] == 0)
            dfs(v, org);
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v; i <= q; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v + n), G[v + n].push_back(u);
    int ans = 0;
    for (int i = 1; i <= n + m; i++)
        if (color[i] == 0)
            dfs(i, ++ans);
    printf("%d\n", ans - 1);
    return 0;
}