// BZ1758.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;
const double eps = 1e-6;

int n, e_lft, e_rig, head[MAX_N], current, max_weight, siz[MAX_N], dep[MAX_N], q[MAX_N], topoidx[MAX_N], topotot;
double ans, dist[MAX_N], qval[MAX_N];
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

int root, val;

void findRoot(int u, int fa, int capacity)
{
    int max_size = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            findRoot(edges[i].to, u, capacity);
            max_size = max(max_size, siz[edges[i].to]), siz[u] += siz[edges[i].to];
        }
    if (max(max_size, capacity - siz[u]) < val)
        val = max(max_size, capacity - siz[u]), root = u;
}

int findRoot(int entryPoint, int capacity) { return root = 0, val = 0x3f3f3f3f, findRoot(entryPoint, 0, capacity), root; }

void bfs(int src, double mid)
{
    queue<pair<int, int> /**/> q;
    q.push(make_pair(src, 0)), topotot = 0;
    while (!q.empty())
    {
        int u = q.front().first, fa = q.front().second;
        q.pop(), topoidx[++topotot] = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!tag[edges[i].to] && edges[i].to != fa)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight - mid, dep[edges[i].to] = dep[u] + 1;
                q.push(make_pair(edges[i].to, u));
            }
    }
}

bool check(int u, double mid)
{
    bool flag = false;
    int gbound = 0;
    for (int i = head[u]; i != -1 && !flag; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            int v = edges[i].to;
            dist[v] = edges[i].weight - mid, dep[v] = 1, bfs(v, mid);
            int front = 1, tail = 0, bound = gbound;
            for (int j = 1; j <= topotot; j++)
            {
                int to = topoidx[j];
                while (bound >= 0 && bound + dep[to] >= e_lft)
                {
                    while (front <= tail && qval[q[tail]] < qval[bound])
                        tail--;
                    q[++tail] = bound, bound--;
                }
                while (front <= tail && dep[to] + q[front] > e_rig)
                    front++;
                if (front <= tail && dist[to] + qval[q[front]] >= 0)
                    flag = true;
            }
            gbound = max(gbound, dep[topoidx[topotot]]);
            for (int j = 1; j <= topotot; j++)
                qval[dep[topoidx[j]]] = max(qval[dep[topoidx[j]]], dist[topoidx[j]]);
        }
    for (int i = 1; i <= gbound; i++)
        qval[i] = -1e12;
    return flag;
}

void solve(int u, int capacity)
{
    tag[u] = true;
    double l = ans, r = max_weight;
    while (l + eps < r)
    {
        double mid = (l + r) / 2.0;
        if (check(u, mid))
            l = mid;
        else
            r = mid;
    }
    ans = l;
    for (int i = head[u], tmp; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            tmp = siz[edges[i].to], solve(findRoot(edges[i].to, tmp), tmp);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &e_lft, &e_rig);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), max_weight = max(max_weight, w);
    solve(findRoot(1, n), n);
    printf("%.3lf\n", ans);
    return 0;
}