// P1349.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
ll mod;
struct matrix
{
    ll mat[2][2];
    matrix() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &mt) const
    {
        matrix empt;
        for (ll i = 0; i < 2; i++)
            for (ll j = 0; j < 2; j++)
                for (ll k = 0; k < 2; k++)
                    empt.mat[i][j] = (empt.mat[i][j] + mat[i][k] * mt.mat[k][j]) % mod;
        return empt;
    }
    matrix operator^(const ll &tim) const
    {
        matrix res, pre = *(this);
        for (ll i = 0; i < 2; i++)
            res.mat[i][i] = 1;
        ll tims = tim;
        while (tims)
        {
            if (tims & 1)
                res = res * pre;
            pre = pre * pre;
            tims >>= 1;
        }
        return res;
    }
};
int main()
{
    ll n;
    matrix a, D;
    scanf("%lld%lld%lld%lld%lld%lld", &D.mat[0][0], &D.mat[1][0], &a.mat[0][1], &a.mat[0][0], &n, &mod);
    D.mat[0][1] = 1;
    if (n == 1)
        return a.mat[0][1];
    if (n == 2)
        return a.mat[0][0];
    D = D ^ (n - 2);
    a = a * D;
    printf("%lld", a.mat[0][0]);
    return 0;
}