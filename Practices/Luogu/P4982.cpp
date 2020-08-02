// P4982.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 130, MAX_K = 330, mod = 1e9 + 7;

int n, m, k, S, limits[MAX_K];

struct matrix
{
    int mat[MAX_N][MAX_N];
    void clear() { memset(mat, 0, sizeof(mat)); }
    int *operator[](const int &rhs) { return mat[rhs]; }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int k = 0; k < S; k++)
            for (int i = 0; i < S; i++)
                if (mat[i][k])
                    for (int j = 0; j < S; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const int &rhs)
    {
        int tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < S; i++)
            ret[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
};

matrix generate(int kth)
{
    matrix ret;
    ret.clear();
    for (int src = 0; src < S; src++)
        for (int dst = 1; dst < S; dst++)
            if ((src & dst) == 0 && (dst & limits[kth]) == dst)
                ret[src][dst] = 1;
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k), S = 1 << m;
    for (int i = 1, p; i <= k; i++)
    {
        scanf("%d", &p);
        for (int j = 1, val; j <= p; j++)
            scanf("%d", &val), limits[i] |= (1 << (val - 1));
    }
    int rem = n % k, seg = n / k;
    matrix ret;
    ret.clear(), ret[0][0] = 1;
    if (seg > 0)
    {
        matrix batch;
        batch.clear();
        for (int i = 0; i < S; i++)
            batch[i][i] = 1;
        for (int i = 1; i <= k; i++)
            batch = batch * generate(i);
        ret = ret * (batch ^ seg);
    }
    for (int i = 1; i <= rem; i++)
        ret = ret * generate(i);
    int ans = 0;
    for (int i = 1; i < S; i++)
        ans = (0LL + ans + ret[0][i]) % mod;
    printf("%d\n", ans);
    return 0;
}