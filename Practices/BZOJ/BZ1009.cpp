// BZ1009.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;

int n, m, mod, nxt[MAX_N];
char str[MAX_N];

struct matrix
{
    int mat[22][22];

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        memset(ret.mat, 0, sizeof(ret.mat));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < m; k++)
                    ret.mat[i][j] = (1LL * ret.mat[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &tim)
    {
        matrix ret, bas = *this;
        memset(ret.mat, 0, sizeof(ret.mat));
        for (int i = 0; i < m; i++)
            ret.mat[i][i] = 1;
        int ti = tim;
        while (ti)
        {
            if (ti & 1)
                ret = ret * bas;
            bas = bas * bas;
            ti >>= 1;
        }
        return ret;
    }
} B;

int main()
{
    scanf("%d%d%d%s", &n, &m, &mod, str + 1);
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j != 0 && str[i] != str[j + 1])
            j = nxt[j];
        if (str[i] == str[j + 1])
            j++;
        nxt[i] = j;
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j <= 9; j++)
        {
            int ptr = i;
            while (ptr != 0 && str[ptr + 1] - '0' != j)
                ptr = nxt[ptr];
            if (str[ptr + 1] - '0' == j)
                ptr++;
            if (ptr != m)
                B.mat[ptr][i] = (B.mat[ptr][i] + 1) % mod;
        }
    B = B ^ n;
    int ans = 0;
    for (int i = 0; i < m; i++)
        ans = (1LL * ans + B.mat[i][0]) % mod;
    printf("%d\n", ans);
    return 0;
}