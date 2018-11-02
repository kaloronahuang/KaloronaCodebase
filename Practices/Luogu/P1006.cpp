// P1006.cpp
// tag:DP

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int m, n;
int map[60][60];
int F[60][60][60][60] = {0};

void init()
{
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
}

void GenerateDP()
{
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                for (int l = 1; l <= n; l++)
                    F[i][j][k][l] = max(
                        max(F[i - 1][j][k - 1][l], F[i - 1][j][k][l - 1]),
                        max(F[i][j - 1][k - 1][l], F[i][j - 1][k][l - 1])),
                    F[i][j][k][l] += (i == k && j == l) ? map[i][j] : map[i][j] + map[k][l];
}

int main()
{
    init();
    GenerateDP();
    cout << F[m][n][m][n];
    return 0;
}