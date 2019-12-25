// P2455.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
const double eps = 1e-8;

int n, idx[MAX_N], tot;
double matrix[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &matrix[i][j]);
    for (int i = 1; i <= n; i++)
    {
        int max_id = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(matrix[max_id][i] - matrix[j][i]) < eps)
            {
                for (int k = i + 1; k <= n; k++)
                    if ((fabs(matrix[max_id][k]) - fabs(matrix[j][k])) > eps &&
                        fabs(matrix[max_id][k]) > fabs(matrix[j][k]))
                    {
                        max_id = j;
                        break;
                    }
            }
            else if (fabs(matrix[max_id][i]) < fabs(matrix[j][i]))
                max_id = j;
        for (int j = 1; j <= n + 1; j++)
            swap(matrix[max_id][j], matrix[i][j]);
        if (!matrix[i][i])
            continue;
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                double rate = matrix[j][i] / matrix[i][i];
                for (int k = i + 1; k <= n + 1; k++)
                    matrix[j][k] -= matrix[i][k] * rate;
            }
    }
    for (int i = 1; i <= n; i++)
        if (!matrix[i][i] && matrix[i][n + 1])
            puts("-1"), exit(0);
    for (int i = 1; i <= n; i++)
        if (!matrix[i][i] && !matrix[i][n + 1])
            puts("0"), exit(0);
    for (int i = 1; i <= n; i++)
        matrix[i][n + 1] /= matrix[i][i];
    for (int i = 1; i <= n; i++)
    {
        printf("x%d=", i);
        if (fabs(matrix[i][n + 1]) < eps)
            printf("0\n");
        else
            printf("%.2lf\n", matrix[i][n + 1]);
    }
    return 0;
}