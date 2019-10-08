// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e6 + 20000;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, head[MAX_N], current, k, si[MAX_N], dep[2020], fat[25][2020];
ll dist[MAX_N], ans[MAX_N];
bool tag[MAX_N];

struct in
{
    char buf[24 << 20], *p1;
    in() : p1(buf) { fread(buf, 1, 24 << 20, stdin); }
    int read()
    {
        int x = 0;
        while (!isdigit(*p1))
            ++p1;
        while (isdigit(*p1))
            x = x * 10 + *p1++ - '0';
        return x;
    }
} io;

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs_path(int u, int fa)
{
    fat[0][u] = fa, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dist[edges[i].to] = dist[u] + edges[i].weight, dfs_path(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 24; i >= 0; i--)
        if (dep[fat[i][x]] >= dep[y])
            x = fat[i][x];
    if (x == y)
        return x;
    for (int i = 24; i >= 0; i--)
        if (fat[i][x] != fat[i][y])
            x = fat[i][x], y = fat[i][y];
    return fat[0][x];
}

int dfs(int u, int fa, ll upper_weight)
{
    ll shortest_dist = INF, shortest_pt = 0;
    ll second_shortest_dist = INF, second_shortest_pt = 0;
    queue<int> *q = new queue<int>();
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            ll wt = 0;
            if (tag[u])
                wt = dist[u];
            else if (upper_weight == -1)
                wt = -1;
            else
                wt = upper_weight;
            int pt = dfs(edges[i].to, u, wt);
            if (pt != 0)
            {
                q->push(pt);
                if (dist[pt] <= shortest_dist)
                {
                    swap(shortest_dist, second_shortest_dist), swap(shortest_pt, second_shortest_pt);
                    shortest_dist = dist[pt], shortest_pt = pt;
                }
                else if (dist[pt] <= second_shortest_dist)
                    second_shortest_dist = dist[pt], second_shortest_pt = pt;
            }
        }
    /*
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            int pt = dfs(edges[i].to, u, (tag[u] ? edges[i].weight : (upper_weight == -1 ? (-1) : (edges[i].weight + upper_weight))));
            if (pt != 0)
            {
                q->push(pt);
                if (shortest_dist > dist[pt])
                {
                    swap(shortest_dist, second_shortest_dist), swap(shortest_pt, second_shortest_pt);
                    shortest_dist = dist[pt], shortest_pt = pt;
                }
                else if (second_shortest_dist > dist[pt])
                    second_shortest_dist = dist[pt], second_shortest_pt = pt;
            }
        }
    */
    if (tag[u])
    {
        if (upper_weight != -1)
            ans[u] = min(ans[u], dist[u] - upper_weight);
        while (!q->empty())
        {
            int v = q->front();
            q->pop();
            ans[v] = min(ans[v], dist[v] - dist[u]);
            ans[u] = min(ans[u], dist[v] - dist[u]);
        }
        delete q;
        return u;
    }
    else
    {
        if (second_shortest_pt == 0)
        {
            if (shortest_pt != 0 && upper_weight != -1)
                ans[shortest_pt] = min(ans[shortest_pt], dist[shortest_pt] - upper_weight);
            return shortest_pt;
        }
        while (!q->empty())
        {
            int v = q->front();
            q->pop();
            if (v != shortest_pt)
            {
                ans[v] = min(ans[v], dist[v] + shortest_dist - (dist[u] << 1));
                if (upper_weight != -1)
                    ans[v] = min(ans[v], dist[v] - upper_weight);
            }
            else
            {
                ans[v] = min(ans[v], dist[v] + second_shortest_dist - (dist[u] << 1));
                if (upper_weight != -1)
                    ans[v] = min(ans[v], dist[v] - upper_weight);
            }
        }
        delete q;
        return shortest_pt;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    memset(ans, 0x3f, sizeof(ans));
    n = io.read();
    for (int i = 2, v, w; i <= n; i++)
        v = io.read(), w = io.read(), addpath(v, i, w), addpath(i, v, w);
    k = io.read();
    for (int i = 1; i <= k; i++)
        si[i] = io.read(), tag[si[i]] = true;
    dfs(1, 0, -1);
    for (int i = 1; i <= k; i++)
        printf("%lld\n", ans[si[i]]);
    return 0;
}