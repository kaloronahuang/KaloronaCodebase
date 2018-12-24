// P2106.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define ll long long
using namespace std;
const ll mod = 1000000007;
struct matrix
{
    ll mat[10][10];
    matrix() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &ma) const
    {
        matrix empt;
        for (ll i = 0; i < 10; i++)
            for (ll j = 0; j < 10; j++)
                for (ll k = 0; k < 10; k++)
                    empt.mat[i][j] = (empt.mat[i][j] + mat[i][k] * ma.mat[k][j] % mod) % mod;
        return empt;
    }
    matrix operator^(const ll &num) const
    {
        ll tim = num;
        matrix pre = *(this);
        matrix tmp;
        for (ll i = 0; i < 10; i++)
            tmp.mat[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                tmp = tmp * pre;
            pre = pre * pre;
            tim >>= 1;
        }
        return tmp;
    }
} premat, Dmat;

int main()
{
    ll k;
    scanf("%lld", &k);
    if (k == 1)
    {
        printf("%lld", 10);
        return 0;
    }
    for (ll i = 1; i < 10; i++)
        premat.mat[0][i] = 1;
    for (ll i = 0; i < 10; i++)
        for (ll j = i - 2; j <= i + 2; j++)
        {
            if (j < 0)
                continue;
            if (j > 9)
                break;
            Dmat.mat[j][i] = 1;
        }
    Dmat = Dmat ^ (k - 1);
    premat = premat * Dmat;
    ll ans = 0;
    for (ll i = 0; i < 10; i++)
        ans += premat.mat[0][i], ans %= mod;
    printf("%lld", ans);
    return 0;
}