// P3706.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, bitnum = 133;

typedef unsigned long long ull;

int n, m;
char str[MAX_N][MAX_N];
double prob[MAX_N], mat[MAX_N][MAX_N];
ull bitpow[MAX_N], pre[MAX_N][MAX_N], suf[MAX_N][MAX_N];

void gauss(int tot)
{
    for (int i = 1; i <= tot; i++)
    {
        int idx = i;
        for (int j = i + 1; j <= tot; j++)
            if (fabs(mat[j][i]) > fabs(mat[idx][i]))
                idx = j;
        if (idx != i)
            for (int j = i; j <= tot + 1; j++)
                swap(mat[i][j], mat[idx][j]);
        for (int j = 1; j <= tot; j++)
            if (i != j)
            {
                double rate = mat[j][i] / mat[i][i];
                for (int k = tot + 1; k >= i; k--)
                    mat[j][k] -= rate * mat[i][k];
            }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    prob[0] = bitpow[0] = 1;
    for (int i = 1; i <= m; i++)
        prob[i] = prob[i - 1] * 0.5, bitpow[i] = bitpow[i - 1] * bitnum;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= m; j++)
            pre[i][j] = pre[i][j - 1] + (str[i][j] - 'A') * bitpow[j];
        for (int j = 1; j <= m; j++)
            suf[i][j] = (suf[i][j - 1] + (str[i][m - j + 1] - 'A')) * bitnum;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                if (pre[i][k] == suf[j][k])
                    mat[i][j] += prob[m - k];
    // construct the matrix;
    for (int i = 1; i <= n; i++)
        mat[i][n + 1] = -prob[m], mat[n + 1][i] = 1;
    mat[n + 1][n + 2] = 1, gauss(n + 1);
    for (int i = 1; i <= n; i++)
        printf("%.10lf\n", mat[i][n + 2] / mat[i][i]);
    return 0;
}