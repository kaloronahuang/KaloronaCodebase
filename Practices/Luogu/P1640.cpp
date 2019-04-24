// P1640.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1001000;
int head[MAX_N], current, matching[MAX_N], n, tmpx, tmpy;
bool vis[11000];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
bool dfs(int u)
{
    if (vis[u])
        return false;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (matching[edges[i].to] == 0 || dfs(matching[edges[i].to]))
        {
            matching[edges[i].to] = u;
            return true;
        }
    return false;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, i), addpath(tmpy, i);
    int ans = 0;
    for (int i = 1; i <= 10000; i++)
    {
        memset(vis, false, sizeof(vis));
        if (dfs(i))
            ans++;
        else
            break;
    }
    printf("%d", ans);
    return 0;
}