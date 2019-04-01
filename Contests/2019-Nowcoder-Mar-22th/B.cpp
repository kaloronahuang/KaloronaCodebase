// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 22000;
int head[MAX_N], current, n, k, tmpx, tmpy, siz[MAX_N], ans, key;
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u, int fa)
{
    siz[u] = 1;
    int most = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == fa)
            continue;
        dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
        most = max(most, siz[edges[i].to]);
    }
    most = max(most, n - siz[u]);
    if (most < key)
        key = most, ans = u;
    if (most == key && ans > u)
        ans = u;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    ans = key = 0x3f3f3f3f;
    dfs(1, 0);
    printf("%d", ans);
    return 0;
}