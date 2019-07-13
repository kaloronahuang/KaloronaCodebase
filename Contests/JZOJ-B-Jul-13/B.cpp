// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int org[MAX_N][MAX_N], mp[MAX_N][MAX_N], n, m, d;

int main()
{
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    memset(org, 0x3f, sizeof(org)), memset(mp, 0x3f, sizeof(mp));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, len; i <= m; i++)
        scanf("%d%d%d", &u, &v, &len), org[u][v] = org[v][u] = len, mp[u][v] = mp[v][u] = 0;
    scanf("%d", &d);
    for (int i = 1, u, v; i <= d; i++)
        scanf("%d%d", &u, &v), mp[u][v] = mp[v][u] = org[u][v];
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
    int A, B;
    scanf("%d%d", &A, &B);
    printf("%d", mp[A][B]);
    return 0;
}