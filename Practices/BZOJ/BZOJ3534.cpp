// BZOJ3534.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55;
const double eps = 1e-10;

int n;
double G[MAX_N][MAX_N], base, mat[MAX_N][MAX_N];

double gauss()
{
    double ret = 1.0;
    for (int i = 1; i < n; i++)
    {
        int key = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(mat[j][i]) > fabs(mat[key][i]))
                key = j;
        if (key != i)
            for (int j = i; j < n; j++)
                swap(mat[i][j], mat[key][j]);
        for (int j = i + 1; j < n; j++)
            if (fabs(mat[j][i]) > eps)
            {
                double rate = mat[j][i] / mat[i][i];
                for (int k = i; k < n; k++)
                    mat[j][k] -= rate * mat[i][k];
            }
    }
    for (int i = 1; i < n; i++)
        ret *= mat[i][i];
    return fabs(ret);
}

int main()
{
    scanf("%d", &n), base = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lf", &G[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                G[i][j] = max(G[i][j], eps);
                G[i][j] = min(G[i][j], 1.0 - eps);
                if (i < j)
                    base *= (1.0 - G[i][j]);
                mat[i][j] -= G[i][j] / (1 - G[i][j]);
            }
    for (int i = 1; i <= n; i++)
    {
        double tmp = 0;
        for (int j = 1; j <= n; j++)
            if (i != j)
                tmp -= mat[i][j];
        mat[i][i] = tmp;
    }
    printf("%.10lf\n", base * gauss());
    return 0;
}