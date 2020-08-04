// FOJ3213.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, head[MAX_N], current, A, B, up[MAX_N], upweight[MAX_N], dep[MAX_N];
ll dist[MAX_N], mdist[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa, bool tagged = false)
{
    if (tagged)
        up[u] = fa, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight, dfs(edges[i].to, u, tagged);
            if (tagged)
                upweight[edges[i].to] = edges[i].weight;
        }
}

ll mdfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            mdist[u] = max(mdist[u], mdfs(edges[i].to, u) + edges[i].weight);
    return mdist[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dist[1] = 0, dfs(1, 0), A = max_element(dist + 1, dist + 1 + n) - dist;
    dist[A] = 0, dfs(A, 0, true), B = max_element(dist + 1, dist + 1 + n) - dist;
    ll diameter = dist[B];
    printf("%lld\n", diameter);
    vector<int> meter_seq;
    int u = B;
    while (u != 0)
        tag[u] = true, meter_seq.push_back(u), u = up[u];
    u = B;
    while (u != 0)
        mdfs(u, 0), u = up[u];
    ll acc = 0;
    int upper = 0, lower = 0;
    for (int u : meter_seq)
    {
        if (mdist[u] == acc)
            upper = u;
        acc += upweight[u];
    }
    acc = 0, reverse(meter_seq.begin(), meter_seq.end());
    for (int u : meter_seq)
    {
        acc += upweight[u];
        if (mdist[u] == acc)
            lower = u;
    }
    printf("%lld\n", max(0, dep[upper] - dep[lower]));
    // cerr << lower << " " << upper << endl;
    return 0;
}