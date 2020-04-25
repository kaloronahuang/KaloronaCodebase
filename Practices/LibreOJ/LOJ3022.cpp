// LOJ3022.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f, dx[2][3] = {{1, 0, -1}, {1, 0, -1}}, dy[2][3] = {{0, -1, 0}, {0, 1, 0}};

int C, R, n, head[MAX_N], current, start_pos, end_pos, cur[MAX_N], dep[MAX_N], xi[MAX_N], yi[MAX_N], ptot, wi[MAX_N];
map<pair<int, int>, int> mp;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

int dinic()
{
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

enum color
{
    grey,
    white
};

color judge(int x, int y)
{
    if (((x & 1) && ((y - 1) % 4 == 0 || (y - 1) % 4 == 1)) || ((!(x & 1)) && ((y + 1) % 4 == 0 || (y + 1) % 4 == 1)))
        return grey;
    return white;
}

void add(int src, int dst, int op)
{
    if (op)
        addtube(start_pos, dst, INF), addtube(dst + n, src, INF);
    else
        addtube(src + n, dst, INF), addtube(dst + n, end_pos, INF);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &C, &R, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &xi[i], &yi[i], &wi[i]), swap(xi[i], yi[i]), mp[make_pair(xi[i], yi[i])] = i;
    start_pos = (n << 1) + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        // grey;
        if (judge(xi[i], yi[i]) == grey && judge(xi[i], yi[i] + 1) == grey && mp.count(make_pair(xi[i], yi[i] + 1)))
        {
            addtube(i, i + n, min(wi[i], wi[mp[make_pair(xi[i], yi[i] + 1)]]));
            for (int d = 0; d < 3; d++)
            {
                int dstx = xi[i] + dx[0][d], dsty = yi[i] + dy[0][d];
                if (mp.count(make_pair(dstx, dsty)))
                    add(i, mp[make_pair(dstx, dsty)], xi[i] & 1);
            }
            for (int d = 0; d < 3; d++)
            {
                int dstx = xi[i] + dx[1][d], dsty = yi[i] + 1 + dy[1][d];
                if (mp.count(make_pair(dstx, dsty)))
                    add(i, mp[make_pair(dstx, dsty)], !(xi[i] & 1));
            }
        }
        else if (judge(xi[i], yi[i]) == white)
            addtube(i, i + n, wi[i]);
    printf("%d\n", dinic());
    return 0;
}