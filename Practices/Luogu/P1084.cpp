// P1084.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], n, m, current, siz[MAX_N], dep[MAX_N];
int fa[25][MAX_N], idx[MAX_N], deg[MAX_N], org[MAX_N];
ll dist[MAX_N];
bool tag[MAX_N], verification[MAX_N];
priority_queue<pr> pq, root_q;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fat, int og)
{
    siz[u] = 1, dep[u] = dep[fat] + 1, org[u] = og, fa[0][u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dist[edges[i].to] = dist[u] + edges[i].weight, dfs(edges[i].to, u, dep[u] == 1 ? edges[i].to : og), siz[u] += siz[edges[i].to];
}

void mark(int u, int fa, bool covered)
{
    if (siz[u] == 1 && covered == false)
        verification[org[u]] = false;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            mark(edges[i].to, u, covered || tag[u]);
}

bool check(ll mid)
{
    // storing the index;
    // initialize;
    memset(verification, true, sizeof(verification));
    memset(tag, false, sizeof(tag));
    while (!pq.empty())
        pq.pop();
    while (!root_q.empty())
        root_q.pop();
    // find the redundent stuff;
    for (int i = 1; i <= idx[0]; i++)
        if (dist[idx[i]] <= mid)
            root_q.push(make_pair(-(mid - dist[idx[i]]), i));
        else
        {
            ll tmp_dist = mid;
            int u = idx[i];
            for (int j = 24; j >= 0; j--)
                if (fa[j][u] != 0 && dist[u] - dist[fa[j][u]] <= tmp_dist)
                    tmp_dist -= dist[u] - dist[fa[j][u]], u = fa[j][u];
            tag[u] = true;
        }
    mark(1, 0, false);
    for (int i = head[1]; i != -1; i = edges[i].nxt)
        if (verification[edges[i].to] == false)
            pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    // fulfill their needs;
    while (!root_q.empty() && !pq.empty())
    {
        pr curt = root_q.top();
        root_q.pop();
        if ((-curt.first) >= -pq.top().first)
            verification[pq.top().second] = true;
        else
            verification[org[idx[curt.second]]] = true;
        while (!pq.empty() && verification[pq.top().second] == true)
            pq.pop();
    }
    return pq.empty();
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), deg[u]++, deg[v]++;
    scanf("%d", &idx[0]);
    for (int i = 1; i <= idx[0]; i++)
        scanf("%d", &idx[i]);
    if (deg[1] > idx[0])
        puts("-1"), exit(0);
    dfs(1, 0, 0);
    for (int i = 1; i < 25; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    ll l = 0, r = 1e18, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}