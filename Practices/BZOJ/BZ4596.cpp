// BZ4596.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 17, mod = 1e9 + 7;

typedef pair<int, int> pii;

int n, mat[MAX_N][MAX_N];
vector<pii> vec[MAX_N];
vector<int> statBox[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int gauss()
{
    int ret = 1;
    for (int i = 1; i < n; i++)
    {
        if (mat[i][i] == 0)
        {
            int key = i;
            for (int j = i + 1; j < n; j++)
                if (mat[j][i] > mat[key][i])
                {
                    key = j;
                    break;
                }
            if (key != i)
                for (int j = i; j < n; j++)
                    swap(mat[i][j], mat[key][j]);
            else
                return 0;
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i + 1; j < n; j++)
        {
            int rate = 1LL * mat[j][i] * inv % mod;
            for (int k = i; k < n; k++)
                mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
        }
    }
    for (int i = 1; i < n; i++)
        ret = 1LL * ret * mat[i][i] % mod;
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, siz, u, v; i <= n - 1; i++)
    {
        scanf("%d", &siz);
        while (siz--)
            scanf("%d%d", &u, &v), vec[i].push_back(make_pair(u, v));
    }
    int ans = 0;
    for (int stat = 1; stat < (1 << (n - 1)); stat++)
    {
        int opt = ((n - 1 - __builtin_popcount(stat)) & 1) ? mod - 1 : 1;
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < n - 1; i++)
            if (stat & (1 << i))
                for (auto &x : vec[i + 1])
                {
                    mat[x.first][x.first]++, mat[x.second][x.second]++;
                    mat[x.first][x.second]--, mat[x.second][x.first]--;
                }
        ans = (0LL + ans + 1LL * opt * gauss() % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}