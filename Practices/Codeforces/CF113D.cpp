// CF113D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 23, MAX_N2 = MAX_N * MAX_N;
bool mp[MAX_N][MAX_N], fact[MAX_N];
int n, m, deg[MAX_N], id[MAX_N][MAX_N], sa, sb, mx;
double pi[MAX_N], mat[MAX_N2][MAX_N2], f[MAX_N], answers[MAX_N];

void fillNode(int x, int y)
{
    int pos = id[x][y];
    mat[pos][pos] = pi[x] * pi[y] - 1.0;
    for (int i = 1; i <= n; i++)
    {
        if (mp[x][i])
            if (i != y)
                mat[pos][id[i][y]] += f[x] * pi[y];
            else
                mat[pos][mx + 1] -= f[x] * pi[y] * fact[y];
        if (mp[i][y])
            if (i != x)
                mat[pos][id[x][i]] += f[y] * pi[x];
            else
                mat[pos][mx + 1] -= f[y] * pi[x] * fact[x];
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][x] && mp[j][y])
                if (i != j)
                    mat[pos][id[i][j]] += f[x] * f[y];
                else
                    mat[pos][mx + 1] -= f[x] * f[y] * fact[j];
        }
    }
}

double solveCases()
{
    for (int i = 1; i <= mx; i++)
    {
        int pos = i;
        for (int j = i + 1; j <= mx; j++)
            if (fabs(mat[j][i]) > fabs(mat[pos][i]))
                pos = j;
        if (pos != i)
            for (int j = 1; j <= mx + 1; j++)
                swap(mat[i][j], mat[pos][j]);
        for (int j = i + 1; j <= mx; j++)
        {
            double tmp = mat[j][i] / mat[i][i];
            for (int k = i; k <= mx + 1; k++)
                mat[j][k] -= mat[i][k] * tmp;
        }
    }
    for (int i = mx; i >= 1; i--)
    {
        for (int j = mx; j > i; j--)
            mat[i][mx + 1] -= mat[i][j] * mat[j][mx + 1];
        mat[i][mx + 1] /= mat[i][i];
    }
    return mat[id[sa][sb]][mx + 1];
}

double solve(int dst)
{
    memset(mat, 0, sizeof(mat));
    memset(fact, 0, sizeof(fact));
    fact[dst] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                fillNode(i, j);
    return solveCases();
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &sa, &sb);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y), mp[x][y] = mp[y][x] = true;
        deg[x]++, deg[y]++;
    }
    if (sa == sb)
    {
        for (int i = 1; i <= n; i++)
            if (i == sa)
                printf("%.10lf ", 1.0);
            else
                printf("%.10lf ", 0.0);
        return 0;
    }
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pi[i]), f[i] = (1.0 - pi[i]) / (1.0 * deg[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                id[i][j] = ++mx;
    for (int i = 1; i <= n; i++)
        printf("%.10lf ", solve(i));
    return 0;
}