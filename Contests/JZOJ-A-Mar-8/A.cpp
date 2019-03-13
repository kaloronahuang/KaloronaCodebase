// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 110, mod = 998244353;
int n, m, p, q;
ll f[MAX_N * 10][MAX_N], g[MAX_N], C[MAX_N][MAX_N], dp[MAX_N][MAX_N], trans[MAX_N][MAX_N];
struct matrix
{
    ll mat[MAX_N][MAX_N];
    matrix() { memset(mat, 0, sizeof(mat)); }
    ll *operator[](const int &pt) { return mat[pt]; }
    matrix operator*(const matrix &mt) const
    {
        matrix ans;
        for (int i = 0; i <= p; i++)
            for (int j = 0; j <= p; j++)
                for (int k = 0; k <= p; k++)
                    ans[i][j] = (ans[i][j] + mat[i][k] * mt.mat[k][j] % mod) % mod;
        return ans;
    }
    matrix operator^(const int &ti) const
    {
        ll tim = ti;
        matrix ans = matrix(), bas = *this;
        for (int i = 0; i <= p; i++)
            ans[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ans = ans * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ans;
    }
};
ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &p, &q);
    f[0][0] = 1;
    C[1][1] = C[1][0] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j < MAX_N; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    
    return 0;
}