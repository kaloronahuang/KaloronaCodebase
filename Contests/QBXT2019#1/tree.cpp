// tree.cpp
#include <bits/stdc++.h>
#define ls (p << 1)
#define rs ((p << 1) | 1)
#define mid ((l + r) >> 1)
using namespace std;
const int MAX_N = 100200;
struct edge
{
    int to, nxt;
    bool mark;
} edges[MAX_N << 1];
int head[MAX_N], color[MAX_N], n, tmpx, tmpy, current, m, ans, dep[MAX_N], fa[MAX_N];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (to == fa[u])
            continue;
        fa[to] = u, dfs(to);
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] != dep[y])
    {
        for (int i = head[fa[x]]; i != -1; i = edges[i].nxt)
            if (edges[i].to == x)
            {
                edges[i].mark = true;
                break;
            }
        x = fa[x];
    }
    if (x == y)
        return x;
    while (x != y)
    {
        for (int i = head[fa[x]]; i != -1; i = edges[i].nxt)
            if (edges[i].to == x)
            {
                edges[i].mark = true;
                break;
            }
        x = fa[x];
        for (int i = head[fa[y]]; i != -1; i = edges[i].nxt)
            if (edges[i].to == y)
            {
                edges[i].mark = true;
                break;
            }
        y = fa[y];
    }
    return x;
}
void statistics(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (to == fa[u])
            continue;
        if (edges[i].mark)
            ans++, edges[i].mark = false;
        statistics(to);
    }
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs(1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    scanf("%d", &m);
    while (m--)
    {
        char opt[10];
        int x;
        scanf("%s%d", opt, &x);
        if (opt[0] == 'U')
            scanf("%d", &color[x]);
        else
        {
            vector<int> vec;
            for (int i = 1; i <= n; i++)
                if (color[i] == x)
                    vec.push_back(i);
            if (vec.size() == 0)
            {
                puts("-1");
                continue;
            }
            while ((vec.size() > 1))
            {
                int x = vec.back(), y;
                vec.pop_back();
                y = vec.back(), vec.pop_back();
                vec.push_back(lca(x, y));
            }
            statistics(1);
            printf("%d\n", ans);
            ans = 0;
        }
    }
    return 0;
}