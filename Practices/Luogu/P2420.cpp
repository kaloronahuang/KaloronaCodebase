// P2420.cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define ll long long
const int maxn = 100020;
int val_table[20][maxn], P[20][maxn], fa[maxn], dep[maxn], q, n;
struct edge
{
    int to, weight;
};
vector<edge> G[maxn];
void dfs(int u, int fat, int d)
{
    fa[u] = fat;
    P[0][u] = fat;
    int siz = G[u].size();
    dep[u] = d;
    for (int i = 1; i <= 19; i++)
        P[i][u] = P[i - 1][P[i - 1][u]],
        val_table[i][u] = (val_table[i - 1][u] ^ val_table[i - 1][P[i - 1][u]]);
    for (int i = 0; i < siz; i++)
    {
        if (G[u][i].to == fat)
            continue;
        val_table[0][G[u][i].to] = G[u][i].weight;
        dfs(G[u][i].to, u, d + 1);
    }
}
ll inquire(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    ll sum = 0;
    for (int i = 19; i >= 0; i--)
        if (dep[P[i][x]] >= dep[y])
            sum ^= val_table[i][x], x = P[i][x];
    if (x == y)
        return sum;
    for (int i = 19; i >= 0; i--)
        if (P[i][x] != P[i][y])
        {
            sum ^= val_table[i][x] ^ val_table[i][y];
            x = P[i][x], y = P[i][y];
        }
    sum ^= (val_table[0][x] ^ val_table[0][y]);
    return sum;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        int src, dst, weight;
        scanf("%d%d%d", &src, &dst, &weight);
        G[src].push_back(edge{dst, weight});
        G[dst].push_back(edge{src, weight});
    }
    dfs(1, 0, 1);
    scanf("%d", &q);
    int x, y;
    for (int i = 0; i < q; i++)
        scanf("%d%d", &x, &y), printf("%lld\n", inquire(x, y));
    return 0;
}