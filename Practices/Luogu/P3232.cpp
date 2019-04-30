// P3232.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 550, MAX_M = MAX_N * MAX_N;
const double eps = 1e-8;

int head[MAX_N], deg[MAX_N], current, n, m, tmpx, tmpy;
int source[MAX_M], destination[MAX_M];
double mat[MAX_N][MAX_N], res[MAX_N], side[MAX_M];
struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &tmpx, &tmpy);
        addpath(tmpx, tmpy), addpath(tmpy, tmpx);
        deg[tmpx]++, deg[tmpy]++;
        source[i] = tmpx, destination[i] = tmpy;
    }
    mat[1][n] = 1;
    for (int pt = 1; pt < n; pt++)
    {
        mat[pt][pt] = 1;
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            if (edges[i].to != n)
                mat[pt][edges[i].to] = -1.0 / double(deg[edges[i].to]);
    }
    for (int i = 1; i < n; i++)
    {
        int now = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(mat[now][i] - 1.0) - fabs(mat[j][i] - 1.0) >= eps)
                now = j;
        if (now != i)
            for (int j = 1; j <= n; j++)
                swap(mat[now][j], mat[i][j]);
        for (int j = n; j >= i; j--)
            mat[i][j] /= mat[i][i];
        for (int j = 1; j < n; j++)
            if (i != j)
                for (int k = n; k >= i; k--)
                    mat[j][k] -= mat[j][i] * mat[i][k];
    }
    for (int i = 1; i <= m; i++)
    {
        if (source[i] != n)
            side[i] += mat[source[i]][n] * (1.0 / (deg[source[i]]));
        if (destination[i] != n)
            side[i] += mat[destination[i]][n] * (1.0 / deg[destination[i]]);
    }
    sort(side + 1, side + 1 + m);
    double ans = 0;
    for (int i = 1; i <= m; i++)
        ans += (m - i + 1) * side[i];
    printf("%.3lf", ans);
    return 0;
}