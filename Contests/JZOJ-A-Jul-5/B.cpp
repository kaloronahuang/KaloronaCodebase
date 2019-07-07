// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, MAX_E = 5050, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, di[MAX_N], s, t, S, T, answer, flag[MAX_N][MAX_N];
int dist[MAX_N], upward[MAX_N], flow[MAX_N];

bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_E << 1];

struct side
{
    int u, v, a, b, L, R;
} original_data[MAX_E << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int lower, int upper, int cost, bool doDi = true)
{
    addpath(src, dst, upper - lower, cost), addpath(dst, src, 0, -cost);
    if (doDi)
        di[dst] += lower, di[src] -= lower;
}

bool spfa()
{
    for (int i = 1; i <= m; i++)
        if (flag[original_data[i].u][original_data[i].v] == original_data[i].L && original_data[i].L < original_data[i].R)
        {
            original_data[i].L++;
            addtube(original_data[i].u, original_data[i].v, 0, 1, original_data[i].a * (2 * original_data[i].L - 1) + original_data[i].b, false);
        }
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(S), dist[S] = 0, vis[S] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].cost && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost, upward[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[T] != INF;
}

void find()
{
    int u = T, i = upward[u];
    while (u != S)
    {
        edges[i].weight--, edges[i ^ 1].weight++;
        answer += edges[i].cost;
        flag[edges[i ^ 1].to][edges[i].to]++, flag[edges[i].to][edges[i ^ 1].to]--;
        u = edges[i ^ 1].to, i = upward[u];
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    s = n + 1, t = s + 1, S = t + 1, T = S + 1;
    for (int i = 1, lft, in, out; i <= n; i++)
    {
        scanf("%d%d%d", &lft, &in, &out);
        if (lft > 0)
            addtube(s, i, lft, lft, 0);
        else if (lft < 0)
            addtube(i, t, -lft, -lft, 0);
        addtube(s, i, 0, INF, in), addtube(i, t, 0, INF, out);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d%d%d", &original_data[i].u, &original_data[i].v,
              &original_data[i].a, &original_data[i].b, &original_data[i].L, &original_data[i].R);
        addtube(original_data[i].u, original_data[i].v, original_data[i].L, original_data[i].L, 0);
        answer += original_data[i].L * (original_data[i].a * original_data[i].L + original_data[i].b);
        flag[original_data[i].u][original_data[i].v] += original_data[i].L;
        flag[original_data[i].v][original_data[i].u] -= original_data[i].L;
    }
    // in searching the possible stream;
    addtube(t, s, 0, INF, 0);
    for (int i = 1; i <= t; i++)
        if (di[i] > 0)
            addtube(S, i, 0, di[i], 0);
        else if (di[i] < 0)
            addtube(i, T, 0, -di[i], 0);
    while (spfa())
        find();
    printf("%d", answer);
    return 0;
}