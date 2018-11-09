#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 200020;
struct edge
{
    int to;
    bitset<1010> cars;
};
vector<edge> G[maxn];
int n, num, m, x, y, fa[maxn], dep[maxn], ans, q;
bitset<1010> check[maxn];
void dfs(int u, int d)
{
    dep[u] = d;
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
        if (G[u][i].to != fa[u])
            dfs(G[u][i].to, d + 1);
}
int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] != dep[y])
        x = fa[x];
    if (x == y)
        return x;
    while (x != y)
        x = fa[x], y = fa[y];
    return x;
}
void mark(int u, int lca, int id)
{
    if (u == lca)
        return;
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
        if (fa[u] == G[u][i].to)
            G[u][i].cars.set(id), mark(fa[u], lca, id);
}
bitset<1010> finalone;
bool flag = false;
void goup(int u, int lca, bitset<1010> prev)
{
    if (u == lca)
    {
        finalone = prev;
        return;
    }
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
        if (G[u][i].to == fa[u])
        {
            if (G[u][i].cars.count() == 0)
            {
                flag = true;
                return;
            }
            if ((prev & G[u][i].cars).count() == 0)
                ans++, prev |= G[u][i].cars;
            goup(G[u][i].to, lca, prev);
            return;
        }
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &num), fa[i] = num, G[i].push_back(edge{num, bitset<1010>(0)}), G[num].push_back(edge{i, bitset<1010>(0)});
    scanf("%d", &m);
    dfs(1, 1);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        int lca = getLCA(x, y);
        if (lca == 1 && !(x == 1 || y == 1))
        {
            bitset<1010> tmp;
            tmp.set(x, y);
            check[i] = tmp;
        }
        mark(x, lca, i), mark(y, lca, i);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        flag = false;
        scanf("%d%d", &x, &y);
        int lca = getLCA(x, y);
        ans = 0, goup(x, lca, 0), goup(y, lca, 0);
        if (lca == 1)
            for (int j = 1; j <= m; j++)
                // TODO;
                if (check[j] && finalone[j] == 1)
                {
                    ans -= 1;
                    break;
                }
        if (flag)
            printf("-1\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
