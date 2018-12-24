// P3233.cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define pr pair<int, int>
using namespace std;
const int MX_N = 300020;
int head[MX_N], current;
struct edge
{
    int to, nxt;
} edges[MX_N << 1];
int fa[MX_N], stfa[20][MX_N], n, dep[MX_N], anses[MX_N], id[MX_N], dfn = 0, q, m;
int tmpx, tmpy, st[MX_N], top = 1, tsiz[MX_N];
pr mx[MX_N];
bool vis[MX_N];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void preprocess()
{
    for (int i = 1; i <= n; i++)
        stfa[0][i] = fa[i];
    for (int tim = 1; tim < 20; tim++)
        for (int u = 1; u <= n; u++)
            stfa[tim][u] = stfa[tim - 1][stfa[tim - 1][u]];
}
int jump(int u, int p)
{
    for (int i = 0; i <= 19; i++)
        if ((p >> i) & 1)
            u = stfa[i][u];
    return u;
}
int getLca(int a, int b)
{
    // b is deeper;
    if (dep[a] > dep[b])
        swap(a, b);
    b = jump(b, dep[b] - dep[a]);
    if (a == b)
        return a;
    for (int tim = 19; tim >= 0; tim--)
        if (stfa[tim][a] != stfa[tim][b])
            a = stfa[tim][a], b = stfa[tim][b];
    return fa[a];
}
void dfs_fa(int u)
{
    id[u] = ++dfn;
    tsiz[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (fa[u] != edges[i].to)
            fa[edges[i].to] = u, dfs_fa(edges[i].to), tsiz[u] += tsiz[edges[i].to];
}
bool compare(const int &a, const int &b) { return id[a] < id[b]; }
void dfs_1(int u)
{
    if (vis[u])
        mx[u] = make_pair(0, u);
    else
        mx[u] = make_pair(1e8, 0);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        dfs_1(to);
        pr tmp = mx[to];
        tmp.first = dep[mx[to].second] - dep[u];
        mx[u] = min(mx[u], tmp);
    }
}
void dfs_2(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        pr p = mx[u];
        p.first += dep[edges[i].to] - dep[u];
        mx[edges[i].to] = min(mx[edges[i].to], p);
        dfs_2(edges[i].to);
    }
    anses[mx[u].second] = max(anses[mx[u].second], tsiz[u]);
}
void dfs_3(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int x = mx[u].second, y = mx[edges[i].to].second;
        if (x != y)
        {
            int dist = dep[x] + dep[y] - (dep[getLca(x, y)] << 1);
            int z = jump(edges[i].to, (dist >> 1) - mx[edges[i].to].first);
            if (dist & 1)
                anses[x] -= tsiz[z];
            else
            {
                if (z != u && z != edges[i].to)
                    z = jump(edges[i].to, (dist >> 1) - mx[edges[i].to].first - (x < y));
                else if (z == u)
                    z = jump(edges[i].to, (dist >> 1) - mx[edges[i].to].first - 1);
                anses[x] -= tsiz[z];
            }
            if (edges[i].to != z)
                anses[y] += tsiz[z] - tsiz[edges[i].to];
        }
        dfs_3(edges[i].to);
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs_fa(1);
    preprocess();
    scanf("%d", &q);
    while (q--)
    {
        current = 0;
        scanf("%d", &m);
        vector<int> harr, arrs;
        for (int i = 1; i <= m; i++)
            scanf("%d", &tmpx), vis[tmpx] = true, harr.push_back(tmpx), anses[tmpx] = 0, arrs.push_back(tmpx);
        sort(harr.begin(), harr.end(), compare);
        // start to build the virtual tree;
        // prep for the stack;
        st[top = 1] = 1, head[1] = -1;
        for (int i = 0; i < m; i++)
        {
            if (harr[i] == 1)
                continue;
            int curtpt = harr[i], lca = getLca(curtpt, st[top]);
            if (lca != st[top])
            {
                while (id[lca] < id[st[top - 1]])
                    addpath(st[top - 1], st[top]), top--;
                if (id[lca] > id[st[top - 1]])
                    head[lca] = -1, addpath(lca, st[top]), st[top] = lca;
                else
                    addpath(lca, st[top--]);
            }
            head[curtpt] = -1, st[++top] = curtpt;
        }
        for (int i = 1; i < top; i++)
            addpath(st[i], st[i + 1]);
        dfs_1(1), dfs_2(1), dfs_3(1);
        for (int i = 0; i < m; i++)
            printf("%d ", anses[arrs[i]]);
        printf("\n");
        for (int i = 0; i < m; i++)
            vis[arrs[i]] = false;
    }
    return 0;
}