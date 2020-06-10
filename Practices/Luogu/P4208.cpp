// P4208.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 31011;

int n, m, mat[MAX_N][MAX_N], val[MAX_N * 10], mem[MAX_N], etot, vtot, idx[MAX_N];

struct edge
{
    int u, v, w;
    bool operator<(const edge &rhs) const { return w < rhs.w; }
} edges[MAX_N * 10], org[MAX_N * 10];

int det(int tot)
{
    int ret = 1;
    for (int i = 2; i <= tot; ++i)
    {
        for (int k = i + 1; k <= tot; ++k)
        {
            while (mat[k][i])
            {
                int d = mat[i][i] / mat[k][i];
                for (int j = i; j <= tot; ++j)
                    mat[i][j] = (mat[i][j] - 1LL * d * mat[k][j] % mod + mod) % mod;
                std::swap(mat[i], mat[k]), ret = -ret;
            }
        }
        ret = 1LL * ret * mat[i][i] % mod, ret = (ret + mod) % mod;
    }
    return ret;
}

void matadd(int x, int y) { mat[x][x]++, mat[y][y]++, mat[x][y] = (0LL + mat[x][y] + mod - 1) % mod, mat[y][x] = (0LL + mat[y][x] + mod - 1) % mod; }

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void meminit()
{
    for (int i = 1; i <= n; i++)
        mem[i] = i;
}

bool kruskal()
{
    meminit();
    for (int i = 1; i <= m; i++)
        if (find(edges[i].u) != find(edges[i].v))
        {
            mem[find(edges[i].u)] = find(edges[i].v);
            org[++etot] = edges[i];
            if (val[vtot] != edges[i].w)
                val[++vtot] = edges[i].w;
        }
    return etot == n - 1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    sort(edges + 1, edges + 1 + m);
    if (!kruskal())
        puts("0"), exit(0);
    int ans = 1;
    for (int i = 1; i <= vtot; i++)
    {
        meminit();
        for (int ptr = 1; ptr < n && org[ptr].w != val[i]; ptr++)
            if (find(org[ptr].u) != find(org[ptr].v))
                mem[find(org[ptr].u)] = find(org[ptr].v);
        for (int ptr = n - 1; ptr >= 1 && org[ptr].w != val[i]; ptr--)
            if (find(org[ptr].u) != find(org[ptr].v))
                mem[find(org[ptr].u)] = find(org[ptr].v);
        int block_tot = 0;
        for (int ptr = 1; ptr <= n; ptr++)
            if (find(ptr) == ptr)
                idx[ptr] = ++block_tot;
        for (int ptr = 1; ptr <= n; ptr++)
            idx[ptr] = idx[find(ptr)];
        memset(mat, 0, sizeof(mat));
        for (int ptr = 1; ptr <= m; ptr++)
            if (edges[ptr].w == val[i])
                matadd(idx[edges[ptr].u], idx[edges[ptr].v]);
        ans = 1LL * ans * det(block_tot) % mod;
    }
    printf("%d\n", ans);
    return 0;
}