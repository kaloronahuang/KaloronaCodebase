// P4494.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int T, n, m, head[MAX_N], current, siz[MAX_N], deg[MAX_N], cut[MAX_N];
int dfn[MAX_N], low[MAX_N], ptot, aff[MAX_N], sub[MAX_N];
char col[MAX_N];
bool flag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

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

void tarjan(int u, int fa, int org)
{
    dfn[u] = low[u] = ++ptot, aff[u] = org;
    siz[u] = col[u] == '1', sub[u] = 0, cut[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to, u, org);
            siz[u] += siz[edges[i].to];
            if (low[edges[i].to] >= dfn[u])
            {
                cut[u]++, flag[u] &= (siz[edges[i].to] & 1) == 0;
                sub[u] += siz[edges[i].to];
            }
            low[u] = min(low[u], low[edges[i].to]);
        }
        else if (edges[i].to != fa)
            low[u] = min(low[u], dfn[edges[i].to]);
    cut[u] -= (fa == 0);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        memset(deg, 0, sizeof(deg)), memset(flag, true, sizeof(flag));
        memset(dfn, 0, sizeof(dfn)), memset(low, 0, sizeof(low));
        scanf("%d%d", &n, &m), ptot = 0;
        for (int i = 1, u, v; i <= m; i++)
        {
            scanf("%d%d", &u, &v);
            addpath(u, v), addpath(v, u);
            deg[u]++, deg[v]++;
        }
        scanf("%s", col + 1);
        int btot = 0, parity = 0;
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0)
                tarjan(i, 0, i), btot++, parity += (siz[i] & 1);
        int idx = m - n + btot;
        printf("%d ", (parity == 0) * fpow(2, idx));
        for (int i = 1; i <= n; i++)
            if (deg[i] == 0)
                printf("%d ", parity - siz[i] == 0 ? fpow(2, idx) : 0);
            else if (flag[i] && (((siz[aff[i]] - (col[i] == '1') - sub[i]) & 1) == 0) && parity - (siz[aff[i]] & 1) == 0)
                printf("%d ", fpow(2, idx - deg[i] + 1 + cut[i]));
            else
                printf("0 ");

        puts("");
    }
    return 0;
}