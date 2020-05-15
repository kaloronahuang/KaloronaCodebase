// CF739E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
const double eps = 1e-8;

int n, a, b, head[MAX_N], current, start_pos, end_pos, flow[MAX_N], pre[MAX_N];
double dist[MAX_N], acc_pi[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
    double cost;
} edges[MAX_N];

void addpath(int src, int dst, int weight, double cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost, head[src] = current++;
}

void addtube(int src, int dst, int weight, double cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    for (int i = 1; i <= end_pos; i++)
        dist[i] = -0x3f3f3f3f3f3f3f3f, vis[i] = false, pre[i] = -1;
    queue<int> q;
    q.push(start_pos), dist[start_pos] = 0, vis[start_pos] = true, flow[start_pos] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] < dist[u] + edges[i].cost - eps && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(edges[i].weight, flow[u]), pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return pre[end_pos] != -1;
}

double mfmc()
{
    double ret = 0;
    while (spfa() && dist[end_pos] >= eps)
    {
        int u = end_pos, flw = flow[end_pos];
        ret += flw * dist[end_pos];
        while (u != start_pos)
        {
            edges[pre[u]].weight -= flw, edges[pre[u] ^ 1].weight += flw;
            u = edges[pre[u] ^ 1].to;
        }
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &a, &b);
    int A = n + 1, B = n + 2;
    start_pos = B + 1, end_pos = B + 2;
    addtube(start_pos, A, a, 0), addtube(start_pos, B, b, 0);
    for (int i = 1; i <= n; i++)
    {
        double pi;
        scanf("%lf", &pi), acc_pi[i] = pi, addtube(A, i, 1, pi);
    }
    for (int i = 1; i <= n; i++)
    {
        double pi;
        scanf("%lf", &pi), acc_pi[i] = -acc_pi[i] * pi, addtube(B, i, 1, pi);
    }
    for (int i = 1; i <= n; i++)
        addtube(i, end_pos, 1, 0), addtube(i, end_pos, 1, acc_pi[i]);
    printf("%.10lf\n", mfmc());
    return 0;
}