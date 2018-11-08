#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 200020;
struct edge
{
    int to, next;
    vector<int> mks;
} edges[maxn << 1];
int head[maxn], fa[maxn], n, m, current = 0;
int P[21][maxn], dep[maxn], q;
bool marks[maxn];
void addpath(int s, int d)
{
    edges[current].to = d;
    edges[current].next = head[s];
    head[s] = current++;
}
void dfs(int u, int d)
{
    dep[u] = d;
    P[0][u] = fa[u];
    for (int i = 1; (1 << i) <= n; i++)
        P[i][u] = P[i - 1][P[i - 1][u]];
    for (int i = head[u]; i != -1; i = edges[i].next)
        if (edges[i].to != fa[u])
            dfs(edges[i].to, d + 1);
}
int inquire(int x, int y)
{
    if (dep[x] > dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[y] >= dep[x] && dep[P[i][y]] >= dep[x] && P[i][y] != 0)
            y = P[i][y];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (P[i][x] != P[i][y])
            x = P[i][x], y = P[i][y];
    return P[0][x];
}
void dfs_edit(int u, int s, int id)
{
    if (dep[u] < dep[s])
        return;
    if (u == s)
        return;
    for (int i = head[u]; i != -1; i = edges[i].next)
        if (edges[i].to == fa[u])
        {
            edges[i].mks.push_back(id);
            dfs_edit(edges[i].to, s, id);
            break;
        }
}
vector<int> ans;
bool flag = true;
void getdfs(int u, int s)
{
    if (u == s)
        return;
    for (int i = head[u]; i != -1; i = edges[i].next)
        if (edges[i].to == fa[u])
        {
            int siz = edges[i].mks.size();
            if (siz == 0)
            {
                flag = false;
                return;
            }
            for (int j = 0; j < siz; j++)
                ans.push_back(edges[i].mks[j]);
            getdfs(fa[u], s);
            break;
        }
}
int main()
{
    freopen("car.in", "r", stdin);
    freopen("car.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &fa[i + 1]), addpath(i + 1, fa[i + 1]), addpath(fa[i + 1], i + 1);
    scanf("%d", &m);
    dfs(1, 0);
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        int lca = inquire(x, y);
        dfs_edit(x, lca, i), dfs_edit(y, lca, i);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        flag = true;
        scanf("%d%d", &x, &y);
        int lca = inquire(x, y);
        ans.resize(0);
        getdfs(x, lca), getdfs(y, lca);
        if (!flag)
        {
            printf("%d\n", -1);
            continue;
        }
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        printf("%d\n", ans.size());
    }
    return 0;
}