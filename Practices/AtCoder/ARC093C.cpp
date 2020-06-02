// ARC093C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

typedef long long ll;

int n, m, mem[MAX_N];
ll X;

struct edge
{
    int src, dst, weight;
    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
} edges[MAX_N << 1];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

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

ll kruskal(int eid)
{
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    ll ret = 0;
    if (eid != 0)
        mem[find(edges[eid].src)] = find(edges[eid].dst), ret += edges[eid].weight;
    for (int i = 1; i <= m; i++)
        if (find(edges[i].src) != find(edges[i].dst))
        {
            ret += edges[i].weight;
            mem[find(edges[i].src)] = find(edges[i].dst);
        }
    return ret;
}

int main()
{
    scanf("%d%d%lld", &n, &m, &X);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].src, &edges[i].dst, &edges[i].weight);
    sort(edges + 1, edges + 1 + m);
    ll min_val = kruskal(0);
    if (min_val > X)
        puts("0"), exit(0);
    int ceq = 0, cgeq = 0;
    for (int i = 1; i <= m; i++)
    {
        ll curt = kruskal(i);
        if (curt == X)
            ceq++;
        else if (curt > X)
            cgeq++;
    }
    if (min_val == X)
        printf("%lld\n", 1LL * ((0LL + fpow(2, ceq) + mod - 2) % mod) * fpow(2, cgeq) % mod);
    else
        printf("%lld\n", (2LL * fpow(2, ceq) % mod + mod - 2) % mod * fpow(2, cgeq) % mod);
    return 0;
}