// rightkings.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_M = 220;

int n, m, b, matrix[MAX_M][MAX_N];

int main()
{
    scanf("%d%d%d", &m, &n, &b);
    for (int i = 1; i <= n; i++)
        for (int j = 1, before = 0x3f3f3f3f, tmp; j <= m; j++)
            scanf("%d", &tmp), matrix[i][j] = matrix[i][j - 1] + max(0, tmp - before), swap(before, tmp);
    for (int i = 2; i <= m; i++)
    {
        int gans = 0;
        for (int j = 1; j <= n; j++)
            gans += matrix[j][i];
        if (gans >= b)
            printf("%d", i), exit(0);
    }
    printf("%d", -1);
    return 0;
}