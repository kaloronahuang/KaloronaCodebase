// P3547.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int n, m, K, A, B, phead[MAX_N], rhead[MAX_N], current, dist[MAX_N];
int ans[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt, pre;
} edges[MAX_N << 2];

void addpath(int *head, int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src], edges[current].pre = -1;
    if (edges[current].nxt != -1)
        edges[edges[current].nxt].pre = current;
    head[src] = current++;
}

void remove(int *head, int u, int eid)
{
    if (edges[eid].pre != -1)
        edges[edges[eid].pre].nxt = edges[eid].nxt;
    if (edges[eid].nxt != -1)
        edges[edges[eid].nxt].pre = edges[eid].pre;
    if (head[u] == eid)
        head[u] = edges[eid].nxt;
}

int main()
{
    memset(phead, -1, sizeof(phead)), memset(rhead, -1, sizeof(rhead));
    scanf("%d%d%d%d%d", &n, &m, &K, &A, &B);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addpath(phead, u, v), addpath(phead, v, u);
        addpath(rhead, u, v), addpath(rhead, v, u);
    }
    memset(dist, -1, sizeof(dist)), memset(ans, 0x3f, sizeof(ans));
    queue<int> q;
    q.push(K), dist[K] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = phead[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] == -1)
                dist[edges[i].to] = dist[u] + 1, q.push(edges[i].to);
    }
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == -1)
            ans[i] = INF;
        else
            ans[i] = min(dist[i] * A, (dist[i] >> 1) * B + (dist[i] & 1) * A);
        dist[i] = -1;
    }
    q.push(K), dist[K] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = phead[u]; i != -1; i = edges[i].nxt)
            tag[edges[i].to] = true;
        for (int i = phead[u]; i != -1; i = edges[i].nxt)
            for (int j = rhead[edges[i].to]; j != -1; j = edges[j].nxt)
                if (dist[edges[j].to] == -1 && tag[edges[j].to] == false)
                {
                    dist[edges[j].to] = dist[u] + 1, remove(rhead, edges[i].to, j);
                    q.push(edges[j].to);
                }
        for (int i = phead[u]; i != -1; i = edges[i].nxt)
            tag[edges[i].to] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] != -1)
            ans[i] = min(ans[i], dist[i] * B);
        dist[i] = -1;
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}