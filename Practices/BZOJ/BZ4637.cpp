// BZ4637.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_E = 2e5 + 200;

typedef long double ld;

int n, m, mem[MAX_N], vtot, val[MAX_E], idx[MAX_N];
ld mat[110][110];

struct edge
{
    int u, v, weight, cost;
    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
} org[MAX_E], edges[MAX_E];

void meminit()
{
    for (int i = 1; i <= n; i++)
        mem[i] = i;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void kruskal()
{
    sort(org + 1, org + 1 + m), meminit();
    int ecnt = 0;
    for (int i = 1; i <= m; i++)
        if (find(org[i].u) != find(org[i].v))
        {
            edges[++ecnt] = org[i];
            mem[find(org[i].u)] = find(org[i].v);
            if (val[vtot] != org[i].weight)
                val[++vtot] = org[i].weight;
        }
}

ld det(int tot)
{
    ld ret = 1;
    for (int i = 2; i <= tot; ++i)
    {
        for (int k = i + 1; k <= tot; ++k)
        {
            while (mat[k][i])
            {
                ld d = mat[i][i] / mat[k][i];
                for (int j = i; j <= tot; ++j)
                    mat[i][j] -= d * mat[k][j];
                std::swap(mat[i], mat[k]), ret = -ret;
            }
        }
        ret *= mat[i][i];
    }
    return ret;
}

void matadd(int x, int y, int w) { mat[x][x] += w, mat[y][y] += w, mat[x][y] -= w, mat[y][x] -= w; }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &org[i].u, &org[i].v, &org[i].weight, &org[i].cost);
    kruskal();
    ld ans = 0;
    for (int i = 1; i <= vtot; i++)
    {
        meminit();
        for (int ptr = 1; ptr < n && edges[ptr].weight != val[i]; ptr++)
            if (find(edges[ptr].u) != find(edges[ptr].v))
                mem[find(edges[ptr].u)] = find(edges[ptr].v);
        for (int ptr = n - 1; ptr >= 1 && edges[ptr].weight != val[i]; ptr--)
            if (find(edges[ptr].u) != find(edges[ptr].v))
                mem[find(edges[ptr].u)] = find(edges[ptr].v);
        int block_tot = 0;
        for (int ptr = 1; ptr <= n; ptr++)
            if (find(ptr) == ptr)
                idx[ptr] = ++block_tot;
        for (int ptr = 1; ptr <= n; ptr++)
            idx[ptr] = idx[find(ptr)];
        memset(mat, 0, sizeof(mat));
        for (int ptr = 1; ptr <= m; ptr++)
            if (org[ptr].weight == val[i])
                matadd(idx[org[ptr].u], idx[org[ptr].v], org[ptr].cost);
        ans += det(block_tot);
    }
    printf("%.5Lf\n", ans);
    return 0;
}