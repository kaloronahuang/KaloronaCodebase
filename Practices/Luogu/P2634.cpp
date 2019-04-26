// P2634.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX_N = 20100;
int head[MAX_N], current, n, tmpx, tmpy, tmpz, capacity;
int size[MAX_N], root_val, root;
ll answer, bucket[3];
bool vis[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void find_root(int u, int fa)
{
    size[u] = 1;
    int max_val = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to] && edges[i].to != fa)
        {
            find_root(edges[i].to, u), size[u] += size[edges[i].to];
            max_val = max(max_val, size[edges[i].to]);
        }
    max_val = max(max_val, capacity - size[u]);
    if (max_val < root_val)
        root_val = max_val, root = u;
}

void clear() { bucket[0] = bucket[1] = bucket[2] = 0; }

void update(int u, int fa, int dist)
{
    bucket[dist]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !vis[edges[i].to])
            update(edges[i].to, u, (dist + edges[i].weight) % 3);
}

ll solve(int u, int dist)
{
    clear(), update(u, 0, dist % 3);
    return bucket[0] * bucket[0] + 2 * bucket[1] * bucket[2];
}

void pdq(int u)
{
    vis[u] = true;
    answer += solve(u, 0);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (vis[edges[i].to])
            continue;
        answer -= solve(edges[i].to, edges[i].weight % 3);
        root = 0, root_val = n;
        capacity = size[edges[i].to];
        find_root(edges[i].to, u);
        pdq(root);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    }
    capacity = root_val = n;
    find_root(1, 0);
    pdq(root);
    ll upper = answer, lower = n * n, d = gcd(upper, lower);
    printf("%lld/%lld", upper / d, lower / d);
    return 0;
}