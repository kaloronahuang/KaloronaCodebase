// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 40000010, mod1 = 998244353, mod2 = 998244352;

int n, k, f[MAX_N];

int quick_pow(int bas, int tim, int mod)
{
    int ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

struct matrix
{
    int mat[201][201];

    matrix() { memset(mat, 0, sizeof(mat)); }

    matrix operator*(const matrix &target)
    {
        matrix ans;
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= k; j++)
                for (int s = 1; s <= k; s++)
                    ans.mat[i][j] = (1LL * ans.mat[i][j] + 1LL * mat[i][s] * target.mat[s][j] % mod2) % mod2;
        return ans;
    }

    matrix operator^(const int &ti)
    {
        int tim = ti;
        matrix ans, bas = *this;
        for (int i = 1; i <= k; i++)
            ans.mat[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ans = ans * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ans;
    }
} A;

int main()
{
    /*
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
    */
    scanf("%d%d", &n, &k);
    for (int i = 2; i <= k; i++)
        A.mat[i][i - 1] = 1;
    for (int i = k; i >= 1; i--)
        scanf("%d", &A.mat[i][k]);
    for (int i = 1; i <= k; i++)
        scanf("%d", &f[i]);
    if (n <= k)
        printf("%d", f[n] % mod1), exit(0);
    n -= k;
    A = A ^ n;
    int ans = 1;
    for (int i = 1; i <= k; i++)
        ans = 1LL * ans * quick_pow(f[i], A.mat[i][k], mod1) % mod1;
    printf("%d", ans);
    return 0;
}