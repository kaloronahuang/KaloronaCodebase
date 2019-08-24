// FOJ4682.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, st, ed, dep[MAX_N], cur[MAX_N];
int n, m, g, sex[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];

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
    q.push(st), dep[st] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                q.push(edges[i].to), dep[edges[i].to] = dep[u] + 1;
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
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

int dinic()
{
    int ans = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(st, INF))
            ans += di;
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &g);
    st = n + m + 1, ed = st + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &sex[i]);
    for (int i = 1, ci; i <= n; i++)
    {
        scanf("%d", &ci);
        if (sex[i] == 0)
            addtube(st, i, ci);
        else
            addtube(i, ed, ci);
    }
    int answer = 0;
    for (int i = 1, wi, certainSex, ki, id, isFriend; i <= m; i++)
    {
        scanf("%d%d%d", &certainSex, &wi, &ki);
        answer += wi;
        while (ki--)
        {
            scanf("%d", &id);
            if (certainSex == 0)
                addtube(i + n, id, INF);
            else
                addtube(id, i + n, INF);
        }
        scanf("%d", &isFriend);
        if (certainSex == 0)
            addtube(st, i + n, wi + ((isFriend) ? g : 0));
        else
            addtube(i + n, ed, wi + ((isFriend) ? g : 0));
    }
    answer -= dinic();
    printf("%d", answer);
    return 0;
}

