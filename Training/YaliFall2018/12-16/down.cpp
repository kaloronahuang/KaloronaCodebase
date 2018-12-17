// down.cpp
// complexity: n^2
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int maxn = 1e6 + 100;
const int mod = 1e9 + 7;
int ls[maxn], rs[maxn], n, head[maxn], current, wt[maxn];
bool vis[maxn];
struct edge
{
    int to, nex;
} edges[maxn << 1];
bool ansbox[maxn];
bool check(int x, int y, int i, int j)
{
    if (i < x)
        swap(x, i), swap(y, j);
    return (y > i && y < j);
}
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nex = head[src];
    head[src] = current++;
}
bool dfs(int u)
{
    if (wt[u] == -1)
        wt[u] = 1;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nex)
    {
        if (wt[edges[i].to] != -1)
        {
            if (wt[edges[i].to] == wt[u])
                return false;
            else
                continue;
        }
        wt[edges[i].to] = wt[u] ^ 1;
        if (!dfs(edges[i].to))
            return false;
    }
    return true;
}
int main()
{
    memset(wt, -1, sizeof(wt));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ls[i], &rs[i]), head[i] = -1;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (check(ls[i], rs[i], ls[j], rs[j]))
                addpath(i, j), addpath(j, i);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            if (dfs(i))
                ans++;
            else
            {
                printf("0");
                return 0;
            }
    ll fans = 1;
    for (int i = 1; i <= ans; i++)
        fans <<= 1, fans %= mod;
    printf("%lld", fans);
    return 0;
}