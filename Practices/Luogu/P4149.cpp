// P4149.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200200;
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
int head[MAX_N], n, k, current, tmpx, tmpy, tmpz, siz[MAX_N];
int standard, center, ans = 0x3f3f3f3f;
int sides[MAX_N], dist[MAX_N];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void dfs(int u, int fa)
{
    siz[u] = 1;
    int strd = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to, w = edges[i].weight;
        if (to == fa)
            continue;
        dfs(to, u);
        siz[u] += siz[to];
        strd = max(strd, siz[to]);
    }
    strd = max(strd, n - siz[u]);
    if (strd > standard)
        center = u;
}
void divide(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (to == fa)
            continue;
        divide(to, u);
    }
    
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    dfs(0, -1);

    return 0;
}