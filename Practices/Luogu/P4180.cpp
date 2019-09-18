// P4180.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 3e5 + 200, MAX_L = 20;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

int head[MAX_N], current, n, m, mem[MAX_N], dep[MAX_N], fa[MAX_L][MAX_N];
ll g[MAX_L][MAX_N][2];

struct edge
{
    int from, to, nxt;
    ll weight;
    bool tag = false;
    bool operator<(const edge &target) const { return weight < target.weight; }
} org[MAX_E], edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            g[0][edges[i].to][0] = edges[i].weight;
            g[0][edges[i].to][1] = -INF;
            dfs(edges[i].to, u);
        }
}

pair<ll, ll> getDist(int x, int y)
{
    ll ans1 = -INF, ans2 = -INF;
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = MAX_L - 1; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
        {
            if (ans1 > g[i][x][0])
                ans2 = max(ans2, g[i][x][0]);
            else
                ans2 = max(ans2, g[i][x][1]), ans1 = g[i][x][0];
            x = fa[i][x];
        }
    if (x == y)
        return make_pair(ans1, ans2);
    for (int i = MAX_L - 1; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
        {
            ans1 = max(ans1, max(g[i][x][0], g[i][y][0]));
            ans2 = max(ans2, g[i][x][0] != ans1 ? g[i][x][0] : g[i][x][1]);
            ans2 = max(ans2, g[i][y][0] != ans1 ? g[i][y][0] : g[i][y][1]);
            x = fa[i][x];
            y = fa[i][y];
        }
    ans1 = max(ans1, max(g[0][x][0], g[0][y][0]));
    ans2 = max(ans2, g[0][x][0] != ans1 ? g[0][x][0] : g[0][x][1]);
    ans2 = max(ans2, g[0][y][0] != ans1 ? g[0][y][0] : g[0][y][1]);
    x = fa[0][x], y = fa[0][y];
    return make_pair(ans1, ans2);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%lld", &org[i].from, &org[i].to, &org[i].weight);
    sort(org + 1, org + 1 + m);
    // do the kruskal;
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    ll pans = 0, ans = 0;
    for (int i = 1, cnt = 0; cnt < n - 1 && i <= m; i++)
    {
        int x = find(org[i].from), y = find(org[i].to);
        if (x != y)
        {
            mem[x] = y, cnt++;
            addpath(org[i].from, org[i].to, org[i].weight), addpath(org[i].to, org[i].from, org[i].weight);
            pans += org[i].weight, org[i].tag = true;
        }
    }
    ans = INF;
    // preprocess;
    dfs(1, 0);
    for (int i = 0; i < MAX_L; i++)
        g[i][1][0] = g[i][1][1] = -INF;
    for (int i = 1; i < MAX_L; i++)
        for (int j = 1; j <= n; j++)
        {
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
            g[i][j][0] = max(g[i - 1][j][0], g[i - 1][fa[i - 1][j]][0]);
            if (g[i - 1][j][0] == g[i - 1][fa[i - 1][j]][0])
                g[i][j][1] = max(g[i - 1][j][1], g[i - 1][fa[i - 1][j]][1]);
            else if (g[i - 1][j][0] > g[i - 1][fa[i - 1][j]][0])
                g[i][j][1] = max(g[i - 1][j][1], g[i - 1][fa[i - 1][j]][0]);
            else
                g[i][j][1] = max(g[i - 1][j][0], g[i - 1][fa[i - 1][j]][1]);
        }
    for (int i = 1; i <= m; i++)
    {
        edge e = org[i];
        if (e.tag)
            continue;
        pair<ll, ll> pr = getDist(e.from, e.to);
        if (e.weight == pr.first)
            ans = min(ans, pans - pr.second + e.weight);
        else if (e.weight > pr.first)
            ans = min(ans, pans - pr.first + e.weight);
    }
    printf("%lld", ans);
    return 0;
}