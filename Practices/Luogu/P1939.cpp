// P1939.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const ll mod = 1000000007;
ll Dmat[3][3] = {{1, 1, 0}, {0, 0, 1}, {1, 0, 0}};
struct matrix
{
    ll mat[3][3];
    matrix() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &ma) const
    {
        matrix ans;
        for (ll i = 0; i < 3; i++)
            for (ll j = 0; j < 3; j++)
                for (ll k = 0; k < 3; k++)
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * ma.mat[k][j] % mod) % mod;
        return ans;
    }
    matrix operator^(const ll &tim) const
    {
        ll tims = tim;
        matrix tmp, pre = *(this);
        for (ll i = 0; i < 3; i++)
            tmp.mat[i][i] = 1;
        while (tims)
        {
            if (tims & 1)
                tmp = tmp * pre;
            pre = pre * pre;
            tims >>= 1;
        }
        return tmp;
    }
};
int main()
{
    ll T;
    scanf("%lld", &T);
    while (T--)
    {
        ll num = 0;
        scanf("%lld", &num);
        if (num == 1 || num == 2 || num == 3)
        {
            printf("1\n");
            continue;
        }
        matrix pre, D;
        for (ll i = 0; i < 3; i++)
            pre.mat[0][i] = 1;
        memcpy(D.mat, Dmat, sizeof(Dmat));
        D = D ^ (num - 3);
        pre = pre * D;
        printf("%lld\n", pre.mat[0][0]);
    }
    return 0;
}