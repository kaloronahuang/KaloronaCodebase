// P3211.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
const double eps = 1e-8;

int n, m, head[MAX_N], current, deg[MAX_N];
double matrix[MAX_N][MAX_N], ans[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[20010];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void build_matrix(int pos)
{
    matrix[n][n] = 1;
    for (int pt = 1; pt <= n - 1; pt++)
    {
        matrix[pt][pt] = deg[pt];
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            if (edges[i].weight & pos)
                matrix[pt][edges[i].to]++, matrix[pt][n + 1]++;
            else
                matrix[pt][edges[i].to]--;
    }
}

void gauss()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
            if (fabs(matrix[j][i]))
            {
                double rate = matrix[j][i] / matrix[i][i];
                for (int k = i; k <= n + 1; k++)
                    matrix[j][k] -= rate * matrix[i][k];
            }
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = i + 1; j <= n; j++)
            matrix[i][n + 1] -= matrix[i][j] * ans[j];
        ans[i] = matrix[i][n + 1] / matrix[i][i];
    }
    memset(matrix, 0, sizeof(matrix));
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int mx = 0;
    for (int i = 1, x, y, z; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        addpath(x, y, z), deg[x]++, mx = max(mx, z);
        if (x != y)
            addpath(y, x, z), deg[y]++;
    }
    double answer = 0;
    for (int i = 1; i <= mx; i <<= 1)
        build_matrix(i), gauss(), answer += ans[1] * i;
    printf("%.3lf", answer);
    return 0;
} // P3211.cpp