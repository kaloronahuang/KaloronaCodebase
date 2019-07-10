// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 10000;

struct matrix
{
    ll mat[3][3];
    matrix operator*(const matrix &target) const
    {
        matrix ans;
        memset(ans.mat, 0, sizeof(ans.mat));
        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= 2; j++)
                for (int k = 1; k <= 2; k++)
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * target.mat[k][j]) % mod;
        return ans;
    }
} zero;

int T;

matrix quick_pow(matrix bas, ll tim)
{
    matrix ans = zero;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas;
        bas = bas * bas;
        tim >>= 1;
    }
    return ans;
}

ll fib(ll n)
{
    if (n == 0)
        return 0;
    matrix init, batch;
    init.mat[1][1] = init.mat[1][2] = 1;
    batch.mat[1][1] = 0, batch.mat[1][2] = batch.mat[2][1] = batch.mat[2][2] = 1;
    batch = quick_pow(batch, n - 1);
    init = init * batch;
    return init.mat[1][1];
}

ll upd(ll num)
{
    while (num < 0)
        num += mod;
    return num % mod;
}

int main()
{
    scanf("%d", &T);
    for (int i = 1; i <= 2; i++)
        zero.mat[i][i] = 1;
    while (T--)
    {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", upd(fib(y + 1) + fib(y) - fib(x - 1) - fib(x)));
    }
}