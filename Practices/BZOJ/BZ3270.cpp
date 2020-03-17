// BZ3270.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;
const double eps = 1e-8;

int n, m, G[MAX_N][MAX_N], deg[MAX_N], A, B;
double pi[MAX_N], mat[MAX_N * MAX_N][MAX_N * MAX_N];

int getId(int x, int y) { return (x - 1) * n + y; }

void build(int x, int y)
{
    int u = getId(x, y);
    mat[u][u] = -1.0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (G[x][i] && G[y][j] && i != j)
            {
                int v = getId(i, j);
                double xpart = (i == x) ? pi[i] : (double(1 - pi[i]) / deg[i]);
                double ypart = (j == y) ? pi[j] : (double(1 - pi[j]) / deg[j]);
                mat[u][v] += xpart * ypart;
            }
}

void gauss(int siz)
{
    for (int i = 1; i <= siz; i++)
    {
        int key = i;
        for (int j = i + 1; j <= siz; j++)
            if (fabs(mat[j][i]) > fabs(mat[key][i]))
                key = j;
        if (key != i)
            for (int j = i; j <= siz + 1; j++)
                swap(mat[i][j], mat[key][j]);
        if (fabs(mat[i][i]) < eps)
            continue;
        for (int j = 1; j <= siz; j++)
            if (i != j && fabs(mat[i][i]) >= eps)
            {
                double rate = mat[j][i] / mat[i][i];
                for (int k = i; k <= siz + 1; k++)
                    mat[j][k] -= rate * mat[i][k];
            }
    }
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &A, &B);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u][v] = G[v][u] = 1, deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pi[i]), G[i][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            build(i, j);
    mat[getId(A, B)][n * n + 1] = -1, gauss(n * n);
    for (int i = 1; i <= n; i++)
        printf("%.6lf ", mat[getId(i, i)][n * n + 1] / mat[getId(i, i)][getId(i, i)]);
    return 0;
}