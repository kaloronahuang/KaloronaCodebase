// BZ4870.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n, p, k, r;

struct matrix
{
    int mat[55][55];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                for (int c = 0; c < k; c++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][c] * rhs.mat[c][j] % p) % p;
        return ret;
    }

    matrix operator^(const ll &rhs)
    {
        ll tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < k; i++)
            ret[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = bas * ret;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} A, B;

int main()
{
    scanf("%d%d%d%d", &n, &p, &k, &r);
    B[0][0] = 1;
    for (int i = 0; i < k; i++)
        A[i][i]++, A[(i + k - 1) % k][i]++;
    ll tot = 1LL * n * k;
    A = B * (A ^ tot);
    printf("%d\n", A[0][r]);
    return 0;
}