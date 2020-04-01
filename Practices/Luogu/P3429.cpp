// P3429.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int n, deg[MAX_N], mat[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, tot, v; i <= n; i++)
    {
        scanf("%d", &tot);
        while (tot--)
            scanf("%d", &v), mat[i][v] = 1, deg[i]++;
        if (deg[i] & 1)
            mat[i][i] = mat[i][n + 1] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        int key = i;
        for (int j = i + 1; j <= n; j++)
            if (mat[j][i] != 0)
            {
                key = j;
                break;
            }
        if (key != i)
            for (int j = i; j <= n + 1; j++)
                swap(mat[i][j], mat[key][j]);
        for (int j = i + 1; j <= n; j++)
            if (mat[j][i] == 1)
                for (int k = i; k <= n + 1; k++)
                    mat[j][k] ^= mat[i][k];
    }
    mat[n][n] = 1;
    // reverse;
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = i + 1; j <= n; j++)
            if (mat[i][j] != 0)
                for (int k = j; k <= n + 1; k++)
                    mat[i][k] ^= mat[j][k];
        mat[i][i] = 1;
    }
    int tot = 0;
    for (int i = 1; i <= n; i++)
        tot += mat[i][n + 1];
    printf("%d\n", tot);
    for (int i = 1; i <= n; i++)
        if (mat[i][n + 1])
            printf("%d ", i);
    puts("");
    return 0;
}