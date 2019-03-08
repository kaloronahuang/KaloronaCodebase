// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 75100, MAX_M = 101000;
int n, m, head[MAX_N], current, tmpx, tmpy, indeg[MAX_N], cnt[MAX_N], longest, dp[MAX_N], obstacle;
struct egde
{
    int to, nxt;
} edges[MAX_M];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++, indeg[dst]++;
}
bool dfs(int u)
{
    cnt[u]++;
    if (dp[u] == longest)
        return true;
    for (int i = head[u]; i != -1; i = edges[i].to)
        if (dfs(edges[i].to))
            return true;
    cnt[u]--;
}
void findLongest()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);
    longest = 0, memset(dp, 0, sizeof(dp));
    while (!q.empty())
    {
        int curt = q.front();
        q.pop();
        if (curt == obstacle)
            continue;
        longest = max(longest, dp[curt]);
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
            if (dp[edges[i].to] < dp[curt] + 1 && edges[i].to != obstacle)
                dp[edges[i].to] = dp[curt] + 1, q.push(edges[i].to);
    }
}
int main()
{
    freopen("chronosphere.in", "r", stdin);
    freopen("chronosphere.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy);
    findLongest();
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            dfs(i);
    for (int i = 1; i <= n; i++)
        if (cnt[obstacle] < cnt[i])
            obstacle = i;
    for (int i = head[obstacle]; i != -1; i = edges[i].nxt)
        indeg[edges[i].to]--;
    findLongest();
    printf("%d %d", obstacle, longest);
    return 0;
}