// A.cpp
// Complexity: O(n)
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 500200;
int head[MAX_N], current, n, tmpx, tmpy, paths[MAX_N];
ll tmpz, goal = 0, answer;
struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];
void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void dfs_1(int u, int fa, ll dis)
{
    ll ans = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs_1(edges[i].to, u, dis + edges[i].weight), ans = max(paths[edges[i].to] + edges[i].weight, ans);
    goal = max(goal, dis), paths[u] = ans;
}
void tune(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            tune(edges[i].to, u), answer += paths[u] - paths[edges[i].to] - edges[i].weight;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d%d%lld", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    dfs_1(1, 0, 0), tune(1, 0);
    printf("%lld", answer);
    return 0;
}