// P2420.cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define ll long long
const int maxn = 100020;
int val_table[20][maxn], P[20][maxn], fa[maxn], dep[maxn];
struct edge
{
    int to, weight;
};
vector<edge> G[maxn];
int n;
void dfs(int u, int fat, int d)
{
    fa[u] = fat;
    P[0][u] = fat;
    int siz = G[u].size();
    dep[u] = d;
    for (int i = 1; (1 << i) <= dep[u]; i++)
    {
        P[i][u] = P[i - 1][P[u][i - 1]];
        val_table[i][u] = val_table[i - 1][u] ^ val_table[i - 1][P[i - 1][u]];
    }
    for (int i = 0; i < siz; i++)
    {
        if (G[u][i].to == fat)
            continue;
        val_table[0][G[u][i].to] = G[u][i].weight;
        dfs(G[u][i].to, u, d + 1);
    }
}
void stprep()
{
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
    return 0;
}