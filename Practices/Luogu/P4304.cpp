// P4304.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220 * 220, dx[8] = {-1, -2, 1, 2, -1, -2, 1, 2}, dy[8] = {-2, -1, -2, -1, 2, 1, 2, 1};

int head[MAX_N], current, n, vis[MAX_N], matching[MAX_N], ncnt;
char mat[220][220];

struct edge
{
    int to, nxt;
} edges[MAX_N * 80];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int getId(int x, int y) { return (x - 1) * n + y; }

int hungry(int u, int org)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] != org)
        {
            vis[edges[i].to] = org;
            if (matching[edges[i].to] == 0 || hungry(matching[edges[i].to], org))
            {
                matching[edges[i].to] = u;
                return 1;
            }
        }
    return 0;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%s", mat[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans += (mat[i][j] == '0');
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j] == '0')
                for (int k = 0; k < 8; k++)
                {
                    int dstx = dx[k] + i, dsty = dy[k] + j;
                    if (dstx <= n && dsty <= n && dstx >= 1 && dsty >= 1 && mat[dstx][dsty] == '0')
                        addpath(getId(i, j), getId(dstx, dsty));
                }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j] == '0' && ((i + j) & 1))
                ans -= hungry(getId(i, j), ++ncnt);
    printf("%d", ans);
    return 0;
}