// CH6802.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220 + 220;

int head[MAX_N], current, n, m, t, vis[MAX_N], matching[MAX_N];
bool tag[MAX_N][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool hungry(int u, int org)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] != org)
        {
            vis[edges[i].to] = org;
            if (matching[edges[i].to] == 0 || hungry(matching[edges[i].to], org))
            {
                matching[edges[i].to] = u;
                return true;
            }
        }
    return false;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &t);
    int tmpx, tmpy;
    while (t--)
        scanf("%d%d", &tmpx, &tmpy), tag[tmpx][tmpy] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (tag[i][j] == false)
                addpath(i, j + n), addpath(j + n, i);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (hungry(i, i))
            ans++;
    printf("%d", ans);
    return 0;
}