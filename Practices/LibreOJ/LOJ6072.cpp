// LOJ6072.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 44, mod = 1e9 + 7;

int n, limit, ci[MAX_N], m, mat[MAX_N][MAX_N], whole[MAX_N], f[MAX_N], binomial[MAX_N][MAX_N];
vector<int> lftSiz[MAX_N], rigSiz[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    for (; tim; tim >>= 1, bas = 1LL * bas * bas % mod)
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
    return ret;
}

void mark(int u, int v) { mat[u][u]++, mat[v][v]++, mat[u][v] = (0LL + mat[u][v] + mod - 1) % mod, mat[v][u] = (0LL + mat[v][u] + mod - 1) % mod; }

int gauss(int siz)
{
    int ret = 1;
    for (int i = 1; i <= siz; i++)
    {
        int key = i;
        for (int j = i; j <= siz; j++)
            if (mat[j][i] != 0)
            {
                key = j;
                break;
            }
        if (key != i)
        {
            ret = mod - ret;
            for (int j = 1; j <= siz; j++)
                swap(mat[key][j], mat[i][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i + 1; j <= siz; j++)
        {
            int rate = 1LL * mat[j][i] * inv % mod;
            for (int k = i; k <= siz; k++)
                mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
        }
    }
    for (int i = 1; i <= siz; i++)
        ret = 1LL * ret * mat[i][i] % mod;
    return ret;
}

int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ci[i]);
        if (ci[i] != -1)
            ci[++m] = ci[i];
    }
    for (int i = 0; i <= n; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j] + binomial[i - 1][j - 1]) % mod;
    }
    int lmid = (m >> 1), rmid = m - lmid;
    for (int stat = 0; stat < (1 << lmid); stat++)
    {
        int siz = __builtin_popcount(stat), sum = 0;
        for (int i = 0; i < lmid; i++)
            if (stat & (1 << i))
                sum += ci[i + 1];
        lftSiz[siz].push_back(sum);
    }
    for (int stat = 0; stat < (1 << rmid); stat++)
    {
        int siz = __builtin_popcount(stat), sum = 0;
        for (int i = 0; i < rmid; i++)
            if (stat & (1 << i))
                sum += ci[i + lmid + 1];
        rigSiz[siz].push_back(sum);
    }
    for (int i = 0; i <= lmid; i++)
        sort(lftSiz[i].begin(), lftSiz[i].end());
    for (int i = 0; i <= rmid; i++)
        sort(rigSiz[i].begin(), rigSiz[i].end());
    for (int i = 0; i <= lmid; i++)
        for (int j = 0; j <= rmid; j++)
        {
            int &src = whole[i + j];
            for (int lptr = 0, rptr = rigSiz[j].size() - 1, siz = lftSiz[i].size(); lptr < siz; lptr++)
            {
                while (rptr >= 0 && rigSiz[j][rptr] + lftSiz[i][lptr] > limit)
                    rptr--;
                src = (0LL + src + rptr + 1) % mod;
            }
        }
    for (int k = 0; k <= n; k++)
    {
        memset(mat, 0, sizeof(mat));
        for (int i = 1; i <= k; i++)
        {
            // typ 1, (1, 1);
            for (int j = i + 1; j <= k; j++)
                mark(i, j);
            // typ 2, (1, 3);
            for (int j = m + 1; j <= n; j++)
                mark(i, j);
        }
        // typ 2, (2, 3);
        for (int i = k + 1; i <= m; i++)
            for (int j = m + 1; j <= n; j++)
                mark(i, j);
        // typ 3, (3, 3);
        for (int i = m + 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                mark(i, j);
        f[k] = gauss(n - 1);
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        int pans = f[i];
        for (int j = 0, opt = ((i - j) & 1) ? mod - 1 : 1; j < i; j++, opt = mod - opt)
            pans = (0LL + pans + 1LL * opt * binomial[i][j] % mod * f[j] % mod) % mod;
        ans = (0LL + ans + 1LL * pans * whole[i] % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}