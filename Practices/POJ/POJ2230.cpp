// POJ2230.cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 10010, MAX_M = 5e4 + 20;

int head[MAX_N], current, n, m, anses[MAX_N], cur;
bool vis[MAX_N];

struct edge
{
    int to, nxt, vis;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    for (int &i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].vis == false)
            edges[i].vis = true, dfs(edges[i].to);
    printf("%d\n", u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1);
    return 0;
}