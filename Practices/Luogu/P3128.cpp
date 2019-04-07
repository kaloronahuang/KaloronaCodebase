// P3128.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 501000;
int head[MAX_N], n, k, current, tag[MAX_N], st[20][MAX_N], tmpx, tmpy, dep[MAX_N], ans;
struct edge
{
    int to, nxt;
} edges[MAX_N << 2];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == st[0][u])
            continue;
        st[0][edges[i].to] = u, dep[edges[i].to] = dep[u] + 1;
        dfs(edges[i].to);
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[st[i][x]] >= dep[y])
            x = st[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (st[i][x] != st[i][y])
            x = st[i][x], y = st[i][y];
    return st[0][x];
}
void getAns(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == st[0][u])
            continue;
        getAns(edges[i].to), tag[u] += tag[edges[i].to];
    }
    ans = max(tag[u], ans);
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dep[1] = 1, dfs(1);
    for (int i = 1; i < 20; i++)
        for (int u = 1; u <= n; u++)
            st[i][u] = st[i - 1][st[i - 1][u]];
    while (k--)
    {
        scanf("%d%d", &tmpx, &tmpy);
        int LCA = lca(tmpx, tmpy);
        tag[tmpx]++, tag[tmpy]++;
        tag[LCA]--, tag[st[0][LCA]]--;
    }
    getAns(1);
    printf("%d", ans);
    return 0;
}