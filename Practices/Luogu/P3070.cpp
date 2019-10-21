// P3070.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 55, dx[4] = {0, 0, 1, -1}, dy[4] = {-1, 1, 0, 0};

char mp[MAX_N][MAX_N], mp_digit[MAX_N * MAX_N];
int n, m, mem[MAX_N * MAX_N], trans[MAX_N * MAX_N], itot;
int head[MAX_N * MAX_N], current, dist[20][MAX_N * MAX_N];
int mp_id[20], dp[(1 << 17)][17];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N * 10];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int getId(int x, int y) { return (x - 1) * m + y; }

inline int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void shortest_path(int src)
{
    int id = trans[src];
    memset(dist[id], 0x3f, sizeof(dist[id]));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[id][src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[id][edges[i].to] > dist[id][u] + (mp_digit[edges[i].to] == 'S'))
                dist[id][edges[i].to] = dist[id][u] + (mp_digit[edges[i].to] == 'S'), pq.push(make_pair(-dist[id][edges[i].to], edges[i].to));
    }
}

void unite(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    mem[x] = y;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mem[getId(i, j)] = getId(i, j), mp_digit[getId(i, j)] = mp[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == 'X')
            {
                if (mp[i - 1][j] == 'X')
                    unite(getId(i - 1, j), getId(i, j));
                if (mp[i][j - 1] == 'X')
                    unite(getId(i, j - 1), getId(i, j));
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (find(getId(i, j)) == getId(i, j) && mp[i][j] == 'X')
                trans[getId(i, j)] = itot, mp_id[itot++] = getId(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] != '.')
                for (int dir = 0; dir < 4; dir++)
                {
                    int sx = i + dx[dir], sy = j + dy[dir];
                    if (mp[sx][sy] != '.' && sx <= n && sx >= 1 && sy <= m && sy >= 1 && find(getId(i, j)) != find(getId(sx, sy)))
                        addpath(find(getId(i, j)), find(getId(sx, sy)));
                }
    for (int i = 0; i < itot; i++)
        shortest_path(mp_id[i]);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < itot; i++)
        dp[1 << i][i] = 0;
    for (int stat = 1; stat < (1 << itot); stat++)
        for (int i = 0; i < itot; i++)
            if (stat & (1 << i))
                for (int k = 0; k < itot; k++)
                    if (!(stat & (1 << k)))
                        dp[stat | (1 << k)][k] = min(dp[stat | (1 << k)][k], dp[stat][i] + dist[i][mp_id[k]]);
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < itot; i++)
        ans = min(ans, dp[(1 << itot) - 1][i]);
    printf("%d", ans);
    return 0;
}