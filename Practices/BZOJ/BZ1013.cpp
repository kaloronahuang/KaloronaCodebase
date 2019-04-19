// BZ1013.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 12;
double mat[MAX_N][MAX_N], c[MAX_N], raw[MAX_N][MAX_N];
int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lf", &raw[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat[i][j] = 2 * (raw[i][j] - raw[i + 1][j]),
            c[i] += raw[i][j] * raw[i][j] - raw[i + 1][j] * raw[i + 1][j];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            if (fabs(mat[j][i]) > 1e-8)
            {
                for (int k = 1; k <= n; k++)
                    swap(mat[j][k], mat[i][k]);
                swap(c[i], c[j]);
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            double rate = mat[j][i] / mat[i][i];
            for (int k = 1; k <= n; k++)
                mat[j][k] -= rate * mat[i][k];
            c[j] -= rate * c[i];
        }
    for (int i = 1; i <= n; i++)
        printf("%.3lf ", c[i] / mat[i][i]);
    return 0;
}