// BZ4675.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_M = 11;

typedef long long ll;

int n, m, head[MAX_N], current, luck[MAX_M], siz[MAX_N], pbuc[MAX_N];
bool tag[MAX_N];
ll ans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int root, val;

void findRoot(int u, int fa, int capacity)
{
    siz[u] = 1;
    int mx_siz = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            findRoot(edges[i].to, u, capacity), siz[u] += siz[edges[i].to];
            mx_siz = max(mx_siz, siz[edges[i].to]);
        }
    if (max(mx_siz, capacity - siz[u]) < val)
        val = max(mx_siz, capacity - siz[u]), root = u;
}

int findRoot(int entryPoint, int capacity) { return root = 0, val = 0x3f3f3f3f, findRoot(entryPoint, 0, capacity), root; }

void collect(int u, int fa, int dep)
{
    for (int i = 1; i <= m; i++)
        if (luck[i] - dep >= 0)
            ans += pbuc[luck[i] - dep];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            collect(edges[i].to, u, dep + 1);
}

void attach(int u, int fa, int dep, int coeff)
{
    pbuc[dep] += coeff;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            attach(edges[i].to, u, dep + 1, coeff);
}

void solve(int u, int capacity)
{
    tag[u] = true, pbuc[0]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            collect(edges[i].to, u, 1), attach(edges[i].to, u, 1, 1);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            attach(edges[i].to, u, 1, -1);
    pbuc[0]--;
    for (int i = head[u], tmp; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            tmp = siz[edges[i].to], solve(findRoot(edges[i].to, tmp), tmp);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &luck[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    solve(findRoot(1, n), n);
    int n1 = (n + 2) / 3, n2 = (n + 1) / 3, n3 = n / 3;
    printf("%.2lf\n", double(1LL * n1 * (n1 - 1) * ans) / double(1LL * n * (n - 1)));
    printf("%.2lf\n", double(1LL * n2 * (n2 - 1) * ans) / double(1LL * n * (n - 1)));
    printf("%.2lf\n", double(1LL * n3 * (n3 - 1) * ans) / double(1LL * n * (n - 1)));
    return 0;
}