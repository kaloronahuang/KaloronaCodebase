// LOJ2171.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

int n, m, pertime, globaltime, kedge, head[MAX_N], current, start_pos, end_pos, dep[MAX_N], cur[MAX_N];
int ui[MAX_N], vi[MAX_N], ansTot, frames[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 10];

struct ansInfo
{
    int a, b, c;
} ansBox[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

bool bfs()
{
    memset(dep, 0, sizeof(dep)), dep[start_pos] = 1;
    queue<int> q;
    q.push(start_pos);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

int main()
{
    /*
    freopen("pro10a.in", "r", stdin);
    freopen("test.out", "w", stdout);
    */
    memset(head, -1, sizeof(head)), memset(cur, -1, sizeof(cur));
    scanf("%d%d%d%d%d", &n, &m, &pertime, &globaltime, &kedge);
    for (int i = 1, u, v; i <= kedge; i++)
        scanf("%d%d", &u, &v), addtube(u, v + n, 1);
    start_pos = n + m + 1, end_pos = n + m + 2;
    for (int i = n + 1; i <= n + m; i++)
        addtube(i, end_pos, 1);
    int max_time = globaltime / pertime, last_flow = 0, cflow = 0;
    for (int T = 1; T <= max_time; T++)
    {
        for (int i = 1; i <= n; i++)
            addtube(start_pos, i, 1);
        while (bfs())
        {
            for (int i = 0; i <= n + m + 2; i++)
                cur[i] = head[i];
            while (int di = dfs(start_pos, INF))
                cflow += di;
        }
        // printf("%.6lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
        if (cflow == last_flow)
            break;
        last_flow = cflow;
    }
    long long totTime = 0;
    for (int i = 0; i < current; i += 2)
    {
        int u = edges[i ^ 1].to, v = edges[i].to;
        if (u != start_pos && v != end_pos && edges[i].weight == 0)
        {
            ansBox[++ansTot] = ansInfo{u, v - n, frames[u] * pertime};
            frames[u]++, totTime += frames[u] * pertime;
        }
    }
    printf("%d %lld\n", cflow, totTime);
    for (int i = 1; i <= ansTot; i++)
        printf("%d %d %d\n", ansBox[i].a, ansBox[i].b, ansBox[i].c);
    // printf("%.6lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}