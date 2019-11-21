// P3855.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1000 * 1000 + 200;

int head[MAX_N], current, n, m, gx, gy, mx, my, tx, ty, dist[MAX_N];
char mp[50][50];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * 10];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int getId(int x, int y) { return (x - 1) * m + y; }

int getSyncId(int ax, int ay, int bx, int by) { return (getId(ax, ay) - 1) * n * m + getId(bx, by); }

bool check(int i, int j) { return mp[i][j] != 'X' && i <= n && i >= 1 && j <= m && j >= 1; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mp[i] + 1);
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == 'G')
                gx = i, gy = j;
            else if (mp[i][j] == 'M')
                mx = i, my = j;
            else if (mp[i][j] == 'T')
                tx = i, ty = j;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int x = 1; x <= n; x++)
                for (int y = 1; y <= m; y++)
                    if (check(i, j) && check(x, y) && mp[i][j] != '#' && mp[x][y] != '#')
                    {
                        // up & down;
                        // up;
                        if (check(i - 1, j) && check(x - 1, y))
                            addpath(getSyncId(i, j, x, y), getSyncId(mp[i - 1][j] == '#' ? i : i - 1, j, mp[x - 1][y] == '#' ? x : x - 1, y));
                        // down;
                        if (check(i + 1, j) && check(x + 1, y))
                            addpath(getSyncId(i, j, x, y), getSyncId(mp[i + 1][j] == '#' ? i : i + 1, j, mp[x + 1][y] == '#' ? x : x + 1, y));
                        // lft button;
                        if (check(i, j - 1) && check(x, y + 1))
                            addpath(getSyncId(i, j, x, y), getSyncId(i, mp[i][j - 1] == '#' ? j : j - 1, x, mp[x][y + 1] == '#' ? y : y + 1));
                        // rig button;
                        if (check(i, j + 1) && check(x, y - 1))
                            addpath(getSyncId(i, j, x, y), getSyncId(i, mp[i][j + 1] == '#' ? j : j + 1, x, mp[x][y - 1] == '#' ? y : y - 1));
                    }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, getSyncId(mx, my, gx, gy))), dist[getSyncId(mx, my, gx, gy)] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + 1)
                dist[edges[i].to] = dist[u] + 1, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
    if (dist[getSyncId(tx, ty, tx, ty)] == 0x3f3f3f3f)
        puts("no");
    else
        printf("%d", dist[getSyncId(tx, ty, tx, ty)]);
    return 0;
}