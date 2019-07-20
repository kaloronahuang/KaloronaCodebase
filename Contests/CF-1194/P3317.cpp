// P3317.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55;
const double eps = 1e-8;

int n;
double matrix[MAX_N][MAX_N], ans = 1;

void solve()
{
    for (int i = 1; i < n; i++)
    {
        int mx = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(matrix[j][i]) > fabs(matrix[mx][i]))
                mx = j;
        if (mx != i)
            for (int j = 1; j < n; j++)
                swap(matrix[i][j], matrix[mx][j]);
        for (int k = i + 1; k < n; k++)
        {
            double rate = matrix[k][i] / matrix[i][i];
            for (int j = i; j < n; j++)
                matrix[k][j] -= matrix[i][j] * rate;
        }
        if (fabs(matrix[i][i]) < 0)
            return (void)(ans = 0);
    }
    for (int i = 1; i < n; i++)
        ans *= matrix[i][i];
    ans = fabs(ans);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lf", &matrix[i][j]);
    double tmp = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (matrix[i][j] < eps)
                matrix[i][j] = eps;
            if (1.0 - matrix[i][j] < eps)
                matrix[i][j] = 1.0 - eps;
            if (i < j)
                tmp *= 1.0 - matrix[i][j];
            matrix[i][j] /= (1.0 - matrix[i][j]);
        }
    for (int i = 1; i <= n; i++)
    {
        matrix[i][i] = 0;
        for (int j = 1; j <= n; j++)
            if (i != j)
                matrix[i][i] -= matrix[i][j];
    }
    solve();
    ans *= tmp;
    printf("%.10lf", ans);
    return 0;
}