// P1129.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 440;
int head[MAX_N], current, T, n, matching[MAX_N], num;
bool vis[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];
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
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        memset(matching, 0, sizeof(matching));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &num);
                if (num == 1)
                    addpath(i, j);
            }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, false, sizeof(vis));
            if (dfs(i))
                ans++;
        }
        if (ans >= n)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}