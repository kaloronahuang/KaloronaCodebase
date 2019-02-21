// POJ3070.cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int MAX_N = 4, mod = 10000;
ll tmp;
struct matrix
{
    ll mat[MAX_N][MAX_N], n, m;
    matrix() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &tar) const
    {
        matrix ans = matrix();
        ans.n = n, ans.m = tar.m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= tar.m; j++)
                for (int k = 1; k <= m; k++)
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * tar.mat[k][j] % mod) % mod;
        return ans;
    }
    matrix operator^(const int &tim) const
    {
        int ti = tim;
        matrix ans, bas = *this;
        for (int i = 1; i <= max(n, m); i++)
            ans.mat[i][i] = 1;
        ans.n = n, ans.m = m;
        while (ti)
        {
            if (ti & 1)
                ans = ans * bas;
            bas = bas * bas;
            ti >>= 1;
        }
        return ans;
    }
} tA, tB;
int main()
{
    while (scanf("%lld", &tmp) && tmp != -1)
    {
        if (tmp == 0)
        {
            puts("0");
            continue;
        }
        if (tmp == 1 || tmp == 2)
        {
            puts("1");
            continue;
        }
        matrix A;
        A.mat[1][1] = 0, A.mat[1][2] = 1, A.mat[2][1] = 1, A.mat[2][2] = 1;
        A.n = 2, A.m = 2;
        matrix F;
        F.n = 1, F.m = 2;
        F.mat[1][1] = 1, F.mat[1][2] = 1;
        A = A ^ (tmp - 2);
        F = F * A;
        printf("%lld\n", F.mat[1][2]);
    }
    return 0;
}