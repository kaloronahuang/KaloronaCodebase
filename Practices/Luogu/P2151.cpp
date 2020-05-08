// P2151.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 150, mod = 45989;

int n, m, t, A, B, head[MAX_N], current;

struct edge
{
    int to, nxt;
} edges[66 * 66];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

struct matrix
{
    int mat[MAX_N][MAX_N];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int k = 0; k < current; k++)
            for (int i = 0; i < current; i++)
                if (mat[i][k])
                    for (int j = 0; j < current; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        matrix ret, bas = *this;
        int tim = rhs;
        ret.clear();
        for (int i = 0; i < current; i++)
            ret[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} init, trans;

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &m, &t, &A, &B), A++, B++;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), u++, v++, addpath(u, v), addpath(v, u);
    for (int src = 0; src < current; src++)
        for (int i = head[edges[src].to]; i != -1; i = edges[i].nxt)
            if ((i ^ src) != 1)
                trans[i][src]++;
    for (int i = head[A]; i != -1; i = edges[i].nxt)
        init[i][0]++;
    init = (trans ^ (t - 1)) * init;
    int ans = 0;
    for (int i = head[B]; i != -1; i = edges[i].nxt)
        ans = (0LL + ans + init[i ^ 1][0]) % mod;
    printf("%d\n", ans);
    return 0;
}