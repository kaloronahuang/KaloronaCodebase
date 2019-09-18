// B.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 510, MAX_E = 3e6 + 200;

int n, m, head[MAX_N * MAX_N], current, sposx, sposy, tposx, tposy, dist[MAX_N * MAX_N];
int upper[MAX_N][MAX_N], lower[MAX_N][MAX_N], lft[MAX_N][MAX_N], rig[MAX_N][MAX_N], stid, edid;
char mp[MAX_N][MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, weight); }

inline int getId(int x, int y) { return m * (x - 1) + y; }

int main()
{
    memset(head, -1, sizeof(head)), memset(mp, '#', sizeof(mp));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == 'C')
                sposx = i, sposy = j;
            else if (mp[i][j] == 'F')
                tposx = i, tposy = j;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == '#')
                continue;
            if (mp[i - 1][j] != '#')
                upper[i][j] = upper[i - 1][j];
            else
                upper[i][j] = i;
            if (mp[i][j - 1] != '#')
                lft[i][j] = lft[i][j - 1];
            else
                lft[i][j] = j;
        }
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
        {
            if (mp[i][j] == '#')
                continue;
            if (mp[i + 1][j] != '#')
                lower[i][j] = lower[i + 1][j];
            else
                lower[i][j] = i;
            if (mp[i][j + 1] != '#')
                rig[i][j] = rig[i][j + 1];
            else
                rig[i][j] = j;
        }
    stid = getId(sposx, sposy), edid = getId(tposx, tposy);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == '#')
                continue;
            if (j != 1 && mp[i][j - 1] != '#')
                addtube(getId(i, j), getId(i, j - 1), 1);
            if (i != 1 && mp[i - 1][j] != '#')
                addtube(getId(i, j), getId(i - 1, j), 1);
            if (j != n && mp[i][j + 1] != '#')
                addtube(getId(i, j), getId(i, j + 1), 1);
            if (i != n && mp[i + 1][j] != '#')
                addtube(getId(i, j), getId(i + 1, j), 1);
            int min_dist = min(abs(upper[i][j] - i), min(abs(lower[i][j] - i), min(abs(lft[i][j] - j), abs(rig[i][j] - j)))) + 1;
            addpath(getId(i, j), getId(upper[i][j], j), min_dist);
            addpath(getId(i, j), getId(lower[i][j], j), min_dist);
            addpath(getId(i, j), getId(i, lft[i][j]), min_dist);
            addpath(getId(i, j), getId(i, rig[i][j]), min_dist);
        }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    dist[stid] = 0, pq.push(make_pair(0, stid));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
    if (dist[edid] == 0x3f3f3f3f)
        puts("nemoguce");
    else
        printf("%d", dist[edid]);
    return 0;
}