// LOJ2548.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 660, MAX_E = 1e5 + 200, INF = 0x3f3f3f3f;
const double pi = acos(-1.0);

int n, head[MAX_N << 1], current, start_pos, end_pos;
double xi[MAX_N], yi[MAX_N], R, tx[MAX_N], ty[MAX_N], dep[MAX_N << 1], S[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

double pow2(double x) { return x * x; }

double getDist(int i, int j) { return sqrt(pow2(xi[i] - tx[j]) + pow2(yi[i] - ty[j])); }

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    dep[start_pos] = 1, q.push(start_pos);
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
    int ret = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
        {
            int di = dfs(edges[i].to, min(flow, edges[i].weight));
            ret += di, flow -= di;
            edges[i].weight -= di, edges[i ^ 1].weight += di;
        }
        if (flow == 0)
            break;
    }
    if (ret == 0)
        dep[u] = 0;
    return ret;
}

int dinic()
{
    int ret = 0;
    while (bfs())
        ret += dfs(start_pos, 2e9);
    return ret;
}

bool check(double mid)
{
    memset(head, -1, sizeof(head)), current = 0;
    start_pos = 0, end_pos = (n << 1) | 1;
    for (int i = 1; i <= n; i++)
        addtube(start_pos, i, 1);
    for (int i = 1; i <= n; i++)
        addtube(i + n, end_pos, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (getDist(i, j) <= mid + 1e-10)
                addtube(i, j + n, 1);
    return dinic() == n;
}

double calc(double theta)
{
    for (int i = 1; i <= n; i++)
    {
        tx[i] = R * cos(theta + (i - 1) * (2 * pi / n));
        ty[i] = R * sin(theta + (i - 1) * (2 * pi / n));
    }
    int top = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            S[++top] = getDist(i, j);
    sort(S + 1, S + top + 1), top = unique(S + 1, S + top + 1) - S - 1;
    int l = 1, r = top;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(S[mid]))
            r = mid;
        else
            l = mid + 1;
    }
    return S[l];
}

int main()
{
    scanf("%d%lf", &n, &R);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &xi[i], &yi[i]);
    double theta = 0, thetaf = calc(theta), ans = thetaf;
    for (double T = pi / n, curt; T > 1e-9; T *= 0.65)
    {
        curt = calc(theta + T), ans = min(ans, curt);
        if (curt < thetaf)
            theta += T, thetaf = curt;
        else
        {
            curt = calc(theta - T), ans = min(ans, curt);
            if (curt < thetaf)
                theta -= T, thetaf = curt;
        }
    }
    printf("%.6lf\n", ans);
    return 0;
}