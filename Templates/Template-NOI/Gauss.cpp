// Gauss.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
const double eps = 1e-9;

int n;
double mat[MAX_N][MAX_N];

bool gauss()
{
    for (int i = 1; i <= n; i++)
    {
        int key = 0;
        for (int j = i; j <= n; j++)
            if (fabs(mat[j][i]) > fabs(mat[key][i]))
                key = j;
        if (fabs(mat[key][i]) < eps)
            return false;
        if (key != i)
            for (int j = 1; j <= n + 1; j++)
                swap(mat[i][j], mat[key][j]);
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                double rate = 1.0 * mat[j][i] / mat[i][i];
                for (int k = 1; k <= n + 1; k++)
                    mat[j][k] -= 1.0 * rate * mat[i][k];
            }
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &mat[i][j]);
    if (gauss())
        for (int i = 1; i <= n; i++)
            printf("%.2lf\n", mat[i][n + 1] / mat[i][i]);
    else
        puts("No Solution");
    return 0;
}