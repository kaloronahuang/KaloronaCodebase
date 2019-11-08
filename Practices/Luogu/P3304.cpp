// P3304.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<long long, int>

using namespace std;

const int MAX_N = 200100;

int head[MAX_N], current, n, fa[MAX_N];
ll dist[MAX_N], longest[MAX_N], comp_edge = 0;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fat)
{
    fa[u] = fat, longest[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            dfs(edges[i].to, u), longest[u] = max(longest[u], longest[edges[i].to] + edges[i].weight);
        }
}

void solve(int u, int fa)
{
    dist[u] = 0, dfs(u, fa);
    while (true)
    {
        int pt, cnt = 0;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa && longest[u] == longest[edges[i].to] + edges[i].weight)
                pt = edges[i].to, cnt++;
        if (cnt >= 2 || cnt == 0)
            break;
        fa = u, u = pt, comp_edge++;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0);
    int pt = 0;
    for (int i = 1; i <= n; i++)
        if (longest[i] > longest[pt])
            pt = i;
    dfs(pt, 0), pt = 0;
    for (int i = 1; i <= n; i++)
        if (longest[i] > longest[pt])
            pt = i;
    ll diameter = longest[pt];
    while ((longest[fa[pt]] << 1) >= diameter)
        pt = fa[pt];
    if ((longest[pt] << 1) == diameter)
    {
        priority_queue<pr> pq;
        dfs(pt, 0);
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            pq.push(make_pair(edges[i].weight + longest[edges[i].to], edges[i].to));
        pr A = pq.top(), B, C;
        pq.pop(), B = pq.top(), pq.pop();
        if (pq.empty())
            comp_edge += 2, solve(A.second, pt), solve(B.second, pt);
        else
        {
            C = pq.top();
        }
    }
    else
        comp_edge++, solve(pt, fa[pt]), solve(fa[pt], pt);
    printf("%lld\n%d", diameter, comp_edge);
    return 0;
}