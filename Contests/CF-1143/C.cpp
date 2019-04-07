// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 2000;
int head[MAX_N], root, current, tmpx, n, fa[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
bool vis[MAX_N], ci[MAX_N];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
bool dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        vis[u] |= dfs(edges[i].to);
    vis[u] |= ci[u];
    return ci[u];
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &fa[i], &ci[i]);
        ci[i] ^= 1;
        if (fa[i] == -1)
            root = i;
        else
            addpath(fa[i], i);
    }
    dfs(root);
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            printf("%d ", i), flag = false;
    if (flag)
        printf("-1");
    return 0;
}