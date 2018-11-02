// P1004.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int map[11][11] = {0};
int F[11][11][11][11] = {0};

void init()
{
    cin >> N;
    int a, b, c;
    cin >> a >> b >> c;
    while (a != 0 || b != 0 || c != 0)
        map[a][b] = c, cin >> a >> b >> c;
}

void GenerateDPTable()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            for (int k = 1; k <= N; k++)
                for (int l = 1; l <= N; l++)
                    F[i][j][k][l] = max(max(F[i - 1][j][k - 1][l], F[i - 1][j][k][l - 1]),
                                        max(F[i][j - 1][k - 1][l], F[i][j - 1][k][l - 1])),
                    F[i][j][k][l] += (i == k && j == l) ? map[i][j] : map[i][j] + map[k][l];
}

int main()
{
    init();
    GenerateDPTable();
    cout << F[N][N][N][N];
    return 0;
}