// P1164.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;
int N, M;
int a[maxn];
int DPTable[maxn][10010];

void init()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> a[i];
    memset(DPTable, 0, sizeof(DPTable));
}

void DP()
{
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= M; j++)
            if (j == a[i])
                DPTable[i][j] = DPTable[i - 1][j] + 1;
            else if (j > a[i])
                DPTable[i][j] = DPTable[i - 1][j] + DPTable[i - 1][j - a[i]];
            else
                DPTable[i][j] = DPTable[i - 1][j];
}

int main()
{
    init();
    DP();
    cout << DPTable[N][M];
    return 0;
}