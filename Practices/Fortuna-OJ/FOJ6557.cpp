// FOJ6557.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, limit;

struct node
{
    int dp[21][21];
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

node pushup(node a, node b)
{
    node ret;
    memset(ret.dp, 0, sizeof(ret.dp));
    for (int i = 1; i <= limit; i++)
        for (int j = i; j <= limit; j++)
            ret.dp[i][j] = (0LL + ret.dp[i][j] + a.dp[1][i] + b.dp[j][limit]);
}

int main()
{
    return 0;
}