// ball.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_U = 22, MAX_R = MAX_U * MAX_U + 20, MAX_N = 40 * MAX_R, MAX_E = (((MAX_R * MAX_R) << 2) + 6 * MAX_R) << 2;
const int INF = 0x3f3f3f3f, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

int n, m, kth, head[MAX_N], current, cur[MAX_N], dep[MAX_N];
int dist[MAX_R][MAX_R], start_pos, end_pos;
char mp[MAX_U][MAX_U];
map<pair<int, int>, int> flowmp[2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

struct property
{
    int x, y, t;
} props[MAX_R << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
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
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (flow == 0 || u == end_pos)
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
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int getId(int x, int y) { return (x - 1) * m + y; }

int ptot, etot;

bool check(ll mid)
{
    memset(head, -1, sizeof(head)), current = 0;
    start_pos = 4 * n * m + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '.')
                addtube(n * m + getId(i, j), 2 * n * m + getId(i, j), 1);
    for (int i = 1; i <= kth; i++)
        addtube(start_pos, i, 1);
    for (int i = kth + 1; i <= (kth << 1); i++)
        addtube(i - kth + 3 * n * m, end_pos, 1);
    for (int i = 1; i <= (kth << 1); i++)
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= m; b++)
                if (mp[a][b] == '.' && dist[getId(a, b)][getId(props[i].x, props[i].y)] != INF && 1LL * dist[getId(a, b)][getId(props[i].x, props[i].y)] * props[i].t <= mid)
                    if (i <= kth)
                        addtube(i, getId(a, b) + n * m, 1);
                    else
                        addtube(getId(a, b) + 2 * n * m, i - kth + 3 * n * m, 1);
    return dinic() == kth;
}

int main()
{
    memset(dist, 0x3f, sizeof(dist));
    // fileIO("ball");
    scanf("%d%d%d", &n, &m, &kth);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= (kth << 1); i++)
        scanf("%d%d%d", &props[i].x, &props[i].y, &props[i].t), flowmp[i > kth][make_pair(props[i].x, props[i].y)]++;
    for (int i = 1; i <= n * m; i++)
        dist[i][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '.')
                for (int d = 0; d < 4; d++)
                    if (mp[i + dx[d]][j + dy[d]] == '.')
                        dist[getId(i, j)][getId(i + dx[d], j + dy[d])] = 1;
    for (int k = 1; k <= n * m; k++)
        for (int i = 1; i <= n * m; i++)
            for (int j = 1; j <= n * m; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    ll l = 0, r = 1e18, res = -1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    // cerr << ptot << " " << etot << endl;
    printf("%lld\n", res);
    return 0;
}