// P2305.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

int n, typ, fa[MAX_N], stk[MAX_N];
int head[MAX_N], current, ptot, order[MAX_N], siz[MAX_N];
ll dp[MAX_N], dist[MAX_N], pi[MAX_N], vi[MAX_N], li[MAX_N];
double slopes[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int root, val;

void dfs_root(int u, int capacity)
{
    siz[u] = 1;
    int mx = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            dfs_root(edges[i].to, capacity), mx = max(mx, siz[edges[i].to]), siz[u] += siz[edges[i].to];
    mx = max(mx, capacity - siz[u]);
    if (mx <= val)
        val = mx, root = u;
}

int find_root(int entry_point, int capacity)
{
    root = 0, val = 0x3f3f3f3f, dfs_root(entry_point, capacity);
    return root;
}

void dfs(int u)
{
    order[++ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            dfs(edges[i].to);
}

bool compare(int a, int b) { return dist[a] - li[a] > dist[b] - li[b]; }

double slope(int y, int x) { return double(dp[x] - dp[y]) / double(dist[x] - dist[y]); }

void solve(int u, int capacity)
{
    if (capacity <= 1)
        return;
    int rt = find_root(u, capacity);
    for (int i = head[rt]; i != -1; i = edges[i].nxt)
        tag[edges[i].to] = true, capacity -= siz[edges[i].to];
    solve(u, capacity);
    ptot = 0;
    for (int i = head[rt]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    sort(order + 1, order + 1 + ptot, compare);
    int top = 0, pt = rt;
    for (int idx = 1; idx <= ptot; idx++)
    {
        int x = order[idx];
        while (pt != fa[u] && dist[pt] >= dist[x] - li[x])
        {
            while (top >= 2 && slopes[top - 1] <= slope(stk[top], pt))
                top--;
            stk[++top] = pt, slopes[top - 1] = slope(stk[top - 1], stk[top]), slopes[top] = -1e18, pt = fa[pt];
        }
        if (top > 0)
        {
            int l = 1, r = top, res;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (slopes[mid] <= pi[x])
                    r = mid - 1, res = mid;
                else
                    l = mid + 1;
            }
            res = stk[res];
            dp[x] = min(dp[x], dp[res] + 1LL * pi[x] * (dist[x] - dist[res]) + vi[x]);
        }
    }
    for (int i = head[rt]; i != -1; i = edges[i].nxt)
        solve(edges[i].to, siz[edges[i].to]);
}

void prep(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dist[edges[i].to] += dist[u], prep(edges[i].to);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &typ);
    for (int i = 2; i <= n; i++)
        scanf("%d%lld%lld%lld%lld", &fa[i], &dist[i], &pi[i], &vi[i], &li[i]);
    for (int i = 2; i <= n; i++)
        addpath(fa[i], i, dist[i]), dp[i] = 1LL << 60;
    prep(1), solve(1, n);
    for (int i = 2; i <= n; i++)
        printf("%lld\n", dp[i]);
    return 0;
}