// P1896.cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 10;
int MAX;
int n, k;
bool sigLine[1 << maxn];
bool doubleLine[1 << maxn][1 << maxn];
int king[1 << maxn];
int dp[maxn][maxn][1 << maxn];

int main()
{
    cin >> n >> k;
    MAX = 1 << n;
    for (int i = 0; i < MAX; i++)
    {
        if (i & (i >> 1))
            continue;
        sigLine[i] = true;
        for (int j = 0; j <= i; j <<= 1)
            if (j & i)
                king[i]++;
    }
    for (int i = 0; i < MAX; i++)
        if (sigLine[i])
            for (int j = 0; j < MAX; j++)
                if (!(!sigLine[j] || (i & j) || i & (j << 1) || i & (j >> 1)))
                    doubleLine[i][j] = true;
    for (int i = 0; i < MAX; i++)
        if (sigLine[i])
            dp[1][king[i]][i] = 1;
}