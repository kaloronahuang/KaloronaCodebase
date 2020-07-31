// CF566C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100, INF = 0x3f3f3f3f;

int n, wi[MAX_N], head[MAX_N], current, siz[MAX_N], anspt;
double deltaFunc[MAX_N], ans = 1e20;
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

int root, max_val;

void find_root(int u, int fa, int capacity)
{
    siz[u] = 1;
    int max_part = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            find_root(edges[i].to, u, capacity), max_part = max(max_part, siz[edges[i].to]);
            siz[u] += siz[edges[i].to];
        }
    max_part = max(max_part, capacity - siz[u]);
    if (max_part < max_val)
        max_val = max_part, root = u;
}

int find_root(int entry_point, int capacity)
{
    root = 0, max_val = INF;
    return find_root(entry_point, 0, capacity), root;
}

double gsum, gdelatsum;

void calc(int u, int fa, int org, double dep)
{
    double tmp = 3.0 / 2.0 * sqrt(dep) * wi[u];
    gsum += 1.0 * wi[u] * sqrt(dep) * dep, gdelatsum += tmp, deltaFunc[org] += tmp;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            calc(edges[i].to, u, org, dep + edges[i].weight);
}

void solve(int u, int capacity)
{
    tag[u] = true, gsum = gdelatsum = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        deltaFunc[edges[i].to] = 0, calc(edges[i].to, u, edges[i].to, edges[i].weight);
    if (gsum < ans)
        ans = gsum, anspt = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to] && gdelatsum - 2.0 * deltaFunc[edges[i].to] < 0)
        {
            int tmp = siz[edges[i].to];
            solve(find_root(edges[i].to, tmp), tmp);
            break;
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    solve(find_root(1, n), n), printf("%d %.10lf\n", anspt, ans);
    return 0;
}