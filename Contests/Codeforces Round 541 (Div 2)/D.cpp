// D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2020;
int head[MAX_N], dep[MAX_N], current, maxdep, n, m, indeg[MAX_N], vis[MAX_N], stat[MAX_N];
vector<int> keypoints;
bool flag = true;
struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N << 2];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u, int fa)
{
    maxdep = max(dep[u], maxdep);
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            if ((vis[edges[i].to] && (dep[u] != dep[edges[i].to] + 1)) || (stat[edges[i].to] && dep[u] != dep[stat[edges[i].to]] + 1))
                puts("No"), exit(0);
            dep[edges[i].to] = dep[u] + 1;
            dfs(edges[i].to, u);
        }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            char opt;
            cin >> opt;
            if (opt == '>')
                addpath(i, j + n), addpath(j + n, i), indeg[i]++;
            else if (opt == '<')
                addpath(i, j + n), addpath(j + n, i), indeg[j]++;
            else if (opt == '=')
                stat[j] = i;
        }
    for (int i = 1; i <= n + m; i++)
        if (indeg[i] == 0)
            dep[i] = 1, dfs(i, 0);
    for (int i = 1; i <= n; i++)
        printf("%d ", maxdep - dep[i] + 1);
    puts("");
    for (int i = 1; i <= m; i++)
        printf("%d ", maxdep - dep[i + n] + 1);
    return 0;
}