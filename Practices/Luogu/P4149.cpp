// P4149.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200200;
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
int head[MAX_N], n, k, current, tmpx, tmpy, tmpz, siz[MAX_N], capacity;
int ans = 1e9, sides[1002000], son[MAX_N], root;
bool vis[MAX_N];
inline int read()
{
    int re = 0, flag = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            flag = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        re = (re << 1) + (re << 3) + ch - '0', ch = getchar();
    return re * flag;
}
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void predfs(int u, int fa)
{
    siz[u] = 1, son[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to, w = edges[i].weight;
        if (to == fa || vis[to])
            continue;
        predfs(to, u);
        siz[u] += siz[to], son[u] = max(siz[to], son[u]);
    }
    son[u] = max(son[u], capacity - siz[u]);
    if (son[u] < son[root])
        root = u;
}
void getMeta(int u, int fa, int cnt, int dist)
{
    if (dist > k)
        return;
    ans = min(ans, sides[k - dist] + cnt);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (to == fa || vis[to])
            continue;
        getMeta(to, u, cnt + 1, dist + edges[i].weight);
    }
}
void update(int u, int fa, int cnt, int dist)
{
    if (dist > k)
        return;
    sides[dist] = min(sides[dist], cnt);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (to == fa || vis[to])
            continue;
        update(to, u, cnt + 1, dist + edges[i].weight);
    }
}
void clear(int u, int fa, int dis)
{
    if (dis >= k)
        return;
    sides[dis] = 1e9;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (vis[to] || fa == to)
            continue;
        clear(to, u, dis + edges[i].weight);
    }
}
void CDQ(int u, int sz)
{
    vis[u] = true, sides[0] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (vis[to])
            continue;
        getMeta(to, u, 1, edges[i].weight);
        update(to, u, 1, edges[i].weight);
    }
    clear(u, 0, 0);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (vis[to])
            continue;
        son[0] = capacity = (siz[to] > siz[u]) ? (sz - siz[u]) : (siz[to]);
        root = 0;
        predfs(to, 0);
        CDQ(root, capacity);
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        addpath(tmpx + 1, tmpy + 1, tmpz), addpath(tmpy + 1, tmpx + 1, tmpz);
    }
    capacity = n;
    son[0] = n, root = 0;
    for (int i = 0; i <= k; i++)
        sides[i] = 1e9;
    predfs(1, 0);
    CDQ(root, n);
    if (ans != 1e9)
        printf("%d", ans);
    else
        printf("-1");
    return 0;
}