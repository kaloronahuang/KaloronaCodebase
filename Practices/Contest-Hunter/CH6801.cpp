// CH6801.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110 * 110 * 10, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int head[MAX_N], current, n, t, vis[MAX_N], matching[MAX_N], ncnt;
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 3];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int getId(int x, int y) { return (x - 1) * n + y; }

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
    scanf("%d%d", &n, &t);
    while (t--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        tag[getId(x, y)] = true;
    }
    int dom = n * n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int d = 0; d < 4; d++)
                if (!tag[getId(i, j)])
                {
                    int dstx = i + dx[d], dsty = j + dy[d];
                    if (dstx <= n && dstx >= 1 && dsty <= n && dsty >= 1 && tag[getId(dstx, dsty)] == false)
                        addpath(getId(i, j) + ((i + j) & 1) * dom, getId(dstx, dsty) + ((dstx + dsty) & 1) * dom);
                }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (((i + j) & 1) == 0)
            {
                memset(vis, 0, sizeof(vis));
                ans += hungry(getId(i, j), ++ncnt);
            }
    printf("%d", ans);
    return 0;
}