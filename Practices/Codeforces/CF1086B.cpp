// CF1086B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, deg[MAX_N], s;

int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), deg[u]++, deg[v]++;
    int leafCnt = 0;
    for (int i = 1; i <= n; i++)
        leafCnt += (deg[i] == 1);
    printf("%.10lf\n", 2.0 * s / leafCnt);
    return 0;
}