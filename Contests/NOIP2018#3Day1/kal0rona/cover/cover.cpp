#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, k;
int h[110];
struct dirt
{
    int e, c;
} dirts[110];
struct state
{
    int val, money;
} dp[110][110];
int min_val[110][110];

void genDP()
{
    for (int i = 1; i <= n; i++)
        min_val[i][i] = h[i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            min_val[i][j] = min(min_val[i][j - 1], h[j]);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
        }
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &h[i], &dirts[i].e, &dirts[i].c);
}