// ARC089E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int n, A, B, d[MAX_N][MAX_N], f[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &A, &B);
    for (int i = 1; i <= A; i++)
        for (int j = 1; j <= B; j++)
            scanf("%d", &d[i][j]);
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            for (int p = 1; p <= A; p++)
                for (int q = 1; q <= B; q++)
                    f[i][j] = max(f[i][j], d[p][q] - i * p - j * q);
    for (int i = 1; i <= A; i++)
        for (int j = 1; j <= B; j++)
        {
            int dist = 1e9;
            for (int p = 0; p <= 100; p++)
                for (int q = 0; q <= 100; q++)
                    dist = min(dist, f[p][q] + i * p + j * q);
            if (dist != d[i][j])
                puts("Impossible"), exit(0);
        }
    puts("Possible"), puts("202 10401");
    for (int i = 1; i <= 100; i++)
        printf("%d %d X\n", i, i + 1);
    for (int i = 102; i < 202; i++)
        printf("%d %d Y\n", i, i + 1);
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            printf("%d %d %d\n", 1 + i, 202 - j, f[i][j]);
    puts("1 202");
    return 0;
}