// CF434E.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, mod, k, x, head[MAX_N], current, vi[MAX_N], in1[MAX_N], out1[MAX_N], siz[MAX_N], kpow[MAX_N], kinv[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int rval, root;

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void find_root(int u, int fa, int capacity)
{
    siz[u] = 1;
    int max_part = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            find_root(edges[i].to, u, capacity), siz[u] += siz[edges[i].to];
            max_part = max(max_part, siz[edges[i].to]);
        }
    if (max(max_part, capacity - siz[u]) < rval)
        rval = max(max_part, capacity - siz[u]), root = u;
}

int find_root(int entry_point, int capacity) { return rval = 0x3f3f3f3f, root = 0, find_root(entry_point, 0, capacity), root; }

map<int, int> mp_src, mp_dst;

void calc(int u, int fa, int dep, int acc, int pre)
{
    int desire_dst = (0LL + x + mod - acc) % mod * kinv[dep] % mod;
    out1[u] += mp_dst[desire_dst];
    in1[u] += mp_src[pre];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            calc(edges[i].to, u, dep + 1, (1LL * acc * k % mod + vi[edges[i].to]) % mod, (0LL + pre + 1LL * vi[edges[i].to] * kpow[dep] % mod) % mod);
}

void collect(int u, int fa, int dep, int acc, int pre)
{
    int src_dist = (1LL * acc * k % mod + vi[u]) % mod;
    mp_src[(0LL + x + mod - src_dist) % mod * kinv[dep + 1] % mod]++;
    int dst_dist = (0LL + pre + 1LL * kpow[dep] * vi[u] % mod) % mod;
    mp_dst[dst_dist]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            collect(edges[i].to, u, dep + 1, src_dist, dst_dist);
}

void solve(int u, int capacity)
{
    tag[u] = true;
    mp_src[(0LL + x + mod - vi[u]) % mod * kinv[1] % mod] = mp_dst[vi[u]] = 1;
    stack<int> sons;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            calc(edges[i].to, u, 1, vi[edges[i].to] % mod, vi[edges[i].to] % mod);
            collect(edges[i].to, u, 1, vi[u] % mod, vi[u] % mod), sons.push(edges[i].to);
        }
    // mp_src[(0LL + x + mod - vi[u]) % mod * kinv[1] % mod]--, mp_dst[vi[u]]--;
    in1[u] += mp_src[0], out1[u] += mp_dst[x];
    mp_src.clear(), mp_dst.clear();
    while (!sons.empty())
    {
        int v = sons.top();
        sons.pop();
        calc(v, u, 1, vi[v] % mod, vi[v] % mod);
        collect(v, u, 1, vi[u] % mod, vi[u] % mod);
    }
    mp_src.clear(), mp_dst.clear();
    for (int i = head[u], tmp; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            tmp = siz[edges[i].to], solve(find_root(edges[i].to, tmp), tmp);
}

void fuck(int u, int fa, int acc)
{
    if (acc == x)
        printf("FUCK at %d\n", u);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            fuck(edges[i].to, u, (1LL * acc * k % mod + vi[edges[i].to]) % mod);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &mod, &k, &x);
    int inv = fpow(k, mod - 2);
    for (int i = kpow[0] = kinv[0] = 1; i <= n; i++)
        scanf("%d", &vi[i]), kpow[i] = 1LL * kpow[i - 1] * k % mod, kinv[i] = 1LL * kinv[i - 1] * inv % mod;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    solve(find_root(1, n), n);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += 2LL * in1[i] * (n - in1[i]) + 2LL * (n - out1[i]) * out1[i] + 1LL * in1[i] * (n - out1[i]) + 1LL * (n - in1[i]) * out1[i];
    printf("%lld\n", 1LL * n * n * n - (ans >> 1));
    return 0;
}