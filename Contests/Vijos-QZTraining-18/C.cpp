// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_E = 1100;

int dist1[MAX_N][MAX_N], dist2[MAX_N][MAX_N], dist3[MAX_N][MAX_N];
int si[MAX_E], ti[MAX_E], ai[MAX_E], bi[MAX_E], fi[MAX_E];
int n, m, intersect_point;

void floyd(int dist[MAX_N][MAX_N], int pt)
{
    for (int i = 1; i <= m; i++)
        if (pt > fi[i])
            dist[si[i]][ti[i]] = min(dist[si[i]][ti[i]], fi[i] * ai[i] + (pt - fi[i]) * bi[i]);
        else
            dist[si[i]][ti[i]] = min(dist[si[i]][ti[i]], pt * ai[i]);
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main()
{
    memset(dist1, 0x3f, sizeof(dist1));
    memset(dist2, 0x3f, sizeof(dist2));
    memset(dist3, 0x3f, sizeof(dist3));
    scanf("%d%d%d%d%d", &n, &m, &si[0], &ti[0], &fi[0]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d%d", &si[i], &ti[i], &ai[i], &bi[i], &fi[i]);
        if ((ai[i] < bi[i]) && (fi[i] < fi[0]))
            intersect_point = i;
    }
    floyd(dist1, fi[0]);
    int ans = dist1[si[0]][ti[0]];
    if (intersect_point)
    {
        floyd(dist2, fi[intersect_point]);
        ai[intersect_point] = bi[intersect_point] = 5000000;
        floyd(dist3, fi[0] - fi[intersect_point]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ans = min(0LL + ans, 0LL + dist1[si[0]][i] + dist2[i][j] + dist3[i][j] + dist1[j][ti[0]]);
    }
    if (ans < 0x3f3f3f3f)
        printf("%d", ans);
    else
        printf("Impossible");
    return 0;
}