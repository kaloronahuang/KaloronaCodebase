// CH0502.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 100200;
bool map[maxn][maxn];
int col[maxn], row[maxn];
int N, M, T;

void solveRow()
{
}

int main()
{
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            int x, y;
            scanf("%d%d", &x, &y), map[x][y];
            row[x]++, col[y]++;
        }
    // check the row;
    int tot = 0;
    for (int i = 1; i <= N; i++)
        tot += row[i];
    if (tot % N)
        solveRow();
}