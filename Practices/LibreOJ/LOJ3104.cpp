// LOJ3104.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

typedef long long ll;

ll n;
char str[MAX_N];

struct matrix
{
    int mat[26][26];
    void clear() { memset(mat, 0, sizeof(mat)); }
    int *operator[](const int &idx) { return mat[idx]; }
    matrix operator*(const matrix &node)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                for (int k = 0; k < 26; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * node.mat[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const ll &idx)
    {
        ll tim = idx;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < 26; i++)
            ret[i][i] = 1;
        for (; tim; tim >>= 1, bas = bas * bas)
            if (tim & 1)
                ret = ret * bas;
        return ret;
    }
} trans, init;

int main()
{
    scanf("%lld%s", &n, str + 1);
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            trans[i][j] = init[0][i] = 1;
    for (int i = 1; str[i + 1] != '\0'; i++)
        trans[str[i] - 'a'][str[i + 1] - 'a'] = 0;
    init = init * (trans ^ (n - 1));
    int ans = 0;
    for (int i = 0; i < 26; i++)
        ans = (0LL + ans + init[0][i]) % mod;
    printf("%d\n", ans);
    return 0;
}