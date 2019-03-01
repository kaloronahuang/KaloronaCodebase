// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 5e3 + 200, MAX_M = 2e5 + 200;
int n, m, head[MAX_N], current, lca[20][MAX_N], dep[MAX_N], circleNode;
int fa[MAX_N], mem[MAX_N], tmpx, tmpy, q;
ll upweight[MAX_N], obstacle[20][MAX_N], tmpz, curtWeight;
char opt[10];
bool vis[MAX_N];
struct edge
{
    int to, nxt, from;
    ll weight;
    edge() { weight = 0; }
    bool operator<(const edge &d) const { return weight < d.weight; }
    bool operator==(const edge &d) const { return (to == d.to && from == d.from) || (to == d.from && from == d.to) && (d.weight == weight); }
} edges[MAX_M << 1], bak[MAX_M << 1], mx;
int find(int x) { return mem[x] == x ? mem[x] : mem[x] = find(mem[x]); }
void unite(int x, int y) { mem[find(x)] = mem[find(y)]; }
void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].weight = weight, edges[current].from = src;
    edges[current].nxt = head[src], head[src] = current++;
}
void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
            fa[edges[i].to] = u, upweight[edges[i].to] = edges[i].weight, dfs(edges[i].to);
}
edge findLoop(int u, int fat)
{
    if (vis[u])
    {
        circleNode = u;
        edge ret;
        ret.weight = -0x3f3f3f3f;
        return ret;
    }
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            edge edg = findLoop(edges[i].to, u);
            if (circleNode == u)
            {
                mx = max(edg, mx);
                circleNode = -1;
                return edge();
            }
            if (circleNode != -1 && circleNode != u)
                return max(edg, edges[i]);
        }
    return edge();
}
void preprocess()
{
    for (int i = 1; i <= n; i++)
        lca[0][i] = fa[i], obstacle[0][i] = upweight[i];
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
        {
            lca[i][j] = lca[i - 1][lca[i - 1][j]];
            obstacle[i][j] = max(obstacle[i - 1][j], obstacle[i - 1][lca[i - 1][j]]);
        }
}
ll getLCA(int x, int y, int &lcapt)
{
    if (dep[x] < dep[y])
        swap(x, y);
    ll ans = 0;
    for (int i = 19; i >= 0; i--)
        if (dep[lca[i][x]] >= dep[y])
            ans = max(ans, obstacle[i][x]), x = lca[i][x];
    if (x == y)
    {
        lcapt = x;
        return ans;
    }
    for (int i = 19; i >= 0; i--)
        if (lca[i][x] != lca[i][y])
            ans = max(ans, max(obstacle[i][x], obstacle[i][y])), x = lca[i][x], y = lca[i][y];
    ans = max(ans, max(obstacle[0][x], obstacle[0][y]));
    lcapt = lca[0][x];
    return ans;
}
bool nim(ll a, ll b)
{
    bool strangeSitu = false;
    ll arr[3];
    arr[1] = a, arr[2] = b;
    for (int i = 1; i <= 2 && !strangeSitu; i++)
    {
        int tot = 0;
        for (int j = 1; j <= 2; j++)
            if (j != i)
                if (j != 1)
                    tot ^= arr[j];
                else
                    tot = arr[j];
        if (tot == arr[i])
            strangeSitu = true;
    }
    return !strangeSitu;
}
void mst()
{
    memset(head, -1, sizeof(head));
    copy(edges, edges + current, bak);
    sort(bak, bak + current);
    int tot = current;
    current = 0;
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 0; i < tot; i++)
    {
        if (find(bak[i].from) == find(bak[i].to) || (bak[i] == mx && mx.weight > curtWeight))
            continue;
        addpath(bak[i].from, bak[i].to, bak[i].weight);
        addpath(bak[i].to, bak[i].from, bak[i].weight);
        unite(bak[i].from, bak[i].to);
    }
}
void update()
{
    memset(vis, 0, sizeof(vis));
    mx = edge();
    circleNode = -1, findLoop(1, 0), mst(), dfs(1), preprocess();
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%lld", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    mst();
    dfs(1), preprocess();
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s", opt + 1);
        if (opt[1] == 'g')
        {
            int m1, m2, b1, b2;
            scanf("%d%d%d%d", &m1, &m2, &b1, &b2);
            ll m = getLCA(m1, m2, m1), b = getLCA(b1, b2, m1);
            if (nim(m, b))
                printf("madoka\n");
            else
                printf("Baozika\n");
        }
        else
        {
            ll u, v, w;
            scanf("%lld%lld%lld", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
            curtWeight = w;
            update();
        }
    }
    return 0;
}