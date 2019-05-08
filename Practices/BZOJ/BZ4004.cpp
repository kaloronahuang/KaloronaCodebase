// BZ4004.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 510;
const double eps = 1e-8;

long double mat[MAX_N][MAX_N], cost[MAX_N];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%Lf", &mat[i][j]);
    for (int i = 1; i <= n; i++)
        scanf("%Lf", &cost[i]);
    int dim = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int now = 0;
        for (int j = dim + 1; j <= n; j++)
            if (fabs(mat[j][i]) > eps && (now == 0 || cost[j] < cost[now]))
                now = j;
        if (now == 0)
            continue;
        dim++, ans += cost[now];
        for (int j = 1; j <= m; j++)
            swap(mat[dim][j], mat[now][j]);
        swap(cost[dim], cost[now]);
        for (int j = 1; j <= n; j++)
            if (j != dim && fabs(mat[j][i]) > eps)
            {
                long double rate = mat[j][i] / mat[dim][i];
                for (int k = i; k <= m; k++)
                    mat[j][k] -= rate * mat[dim][k];
            }
    }
    printf("%d %d", dim, ans);
    return 0;
}