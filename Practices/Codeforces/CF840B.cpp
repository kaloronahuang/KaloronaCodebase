// CF840B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, di[MAX_N], head[MAX_N], current;
set<int> ansBox;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool dfs(int u)
{
    vis[u] = true;
    int curt = di[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to] && dfs(edges[i].to))
            curt ^= 1, ansBox.insert(edges[i].weight);
    if (di[u] == -1)
        curt = 0;
    return curt;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    bool flag = false;
    int xbit = 0, pt = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &di[i]);
        if (di[i] != -1)
            xbit ^= (di[i] & 1);
        else
            flag = true, pt = i;
    }
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v, i), addpath(v, u, i);
    if ((xbit & 1) && (!flag))
        puts("-1"), exit(0);
    dfs(pt), printf("%lld\n", 1LL * ansBox.size());
    for (int x : ansBox)
        printf("%d\n", x);
    return 0;
}