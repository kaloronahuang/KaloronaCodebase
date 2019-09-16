// FOJ4822.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10010, MAX_E = 100100;

int head[MAX_N], current, n, m;
short color[MAX_N];
bool flag = true;

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    if (flag == false)
        return;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (color[edges[i].to] != -1)
            flag &= (color[edges[i].to] ^ color[u] == 1);
        else
            color[edges[i].to] = color[u] ^ 1, dfs(edges[i].to);
}

int main()
{
    freopen("perfect.in", "r", stdin);
    freopen("perfect.out", "w", stdout);
    memset(head, -1, sizeof(head));
    memset(color, -1, sizeof(color));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n && flag; i++)
        if (color[i] == -1)
            color[i] = 0, dfs(i);
    if (!flag)
        puts("NO");
    else
    {
        puts("YES");
        for (int i = 1; i <= n; i++)
            printf("%d ", color[i]);
    }
    return 0;
}