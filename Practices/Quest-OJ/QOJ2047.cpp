// QOJ2047.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7;
typedef long long ll;

ll n;
int m;

struct matrix
{
    int mat[MAX_N][MAX_N];

    int *operator[](const int &rhs) { return mat[rhs]; }

    void clear() { memset(mat, 0, sizeof(mat)); }

    int travel(int pt, int offset) { return (pt == m + 1) ? pt : (pt + offset - 1) % m + 1; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 1; i <= m + 1; i++)
            for (int j = 1; j <= m + 1; j++)
                for (int k = 1; k <= m + 1; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix move(ll x)
    {
        x %= m;
        matrix ret;
        ret.clear();
        for (int i = 1; i <= m + 1; i++)
            for (int j = 1; j <= m + 1; j++)
                ret[travel(i, x)][travel(j, x)] = mat[i][j];
        return ret;
    }
} E, prefix[MAX_N];

int ans[MAX_N], tmp[MAX_N];
vector<int> vec;

int main()
{
    scanf("%lld%d", &n, &m);
    E.clear();
    for (int i = 1; i <= m + 1; i++)
        E[i][i] = 1;
    prefix[0] = E;
    for (int i = 1; i <= m + 1; i++)
        prefix[0][1][i] = 1;
    ans[m + 1] = 1;
    int tot = 0;
    while (n)
    {
        vec.push_back(n % m);
        matrix curt = prefix[tot];
        prefix[++tot] = E;
        ll tim = m, dep = 0;
        while (tim)
        {
            if (tim & 1LL)
                prefix[tot] = prefix[tot] * curt.move((tim ^ 1LL) << dep);
            curt = curt.move(1LL << dep) * curt;
            tim >>= 1LL, dep++;
        }
        n /= m;
    }
    int dep = 0;
    for (int idx = vec.size() - 1; idx >= 0; idx--)
    {
        int u = vec[idx];
        if (u)
            for (int t = 0; t <= u - 1; t++)
            {
                memcpy(tmp, ans, sizeof(tmp)), memset(ans, 0, sizeof(ans));
                matrix target = prefix[idx].move((0LL + dep + t) % m);
                for (int i = 1; i <= m + 1; i++)
                    for (int j = 1; j <= m + 1; j++)
                        ans[i] = (1LL * ans[i] + 1LL * tmp[j] * target[i][j] % mod) % mod;
            }
        dep = (0LL + dep + u) % mod;
    }
    int sum = 0;
    for (int i = 1; i <= m + 1; i++)
        sum = (1LL * sum + ans[i]) % mod;
    printf("%d\n", sum);
    return 0;
}