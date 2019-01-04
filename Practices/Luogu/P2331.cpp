// P2331.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, m, k, mat[110][3];
int dp[110][15][5];
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]);
    if (m == 1)
    {
        
    }
    else
    {
    }
    return 0;
}