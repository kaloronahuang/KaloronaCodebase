// P4251.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 260, INF = 0x3f3f3f3f;

int head[int(1e5) + 200], current, n, m, k, mat[MAX_N][MAX_N], dep[int(1e5) + 200];
int st, ed, cur[int(1e5) + 200];
vector<int> vec;

struct edge
{
    int to, nxt, weight;
} edges[int(2e6) + 2000];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight), addpath(dst, src, 0);
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
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
        return flow;
    int sum = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                flow -= di, sum += di;
            }
    return sum;
}

int dinic()
{
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(st, INF))
            ret += di;
    }
    return ret;
}

bool check(int mid)
{
    memset(head, -1, sizeof(head)), current = 0;
    st = n + m + 1, ed = st + 1;
    for (int i = 1; i <= n; i++)
        addtube(st, i, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mat[i][j] <= vec[mid - 1])
                addtube(i, j + n, 1);
    for (int i = 1; i <= m; i++)
        addtube(i + n, ed, 1);
    return dinic() >= n - k + 1;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]), vec.push_back(mat[i][j]);
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int l = 1, r = vec.size(), ans = 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", vec[ans - 1]);
    return 0;
}