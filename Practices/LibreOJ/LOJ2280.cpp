// LOJ2280.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7;

int T, h, w, m, n, xp1[MAX_N], yp1[MAX_N], xp2[MAX_N], yp2[MAX_N], vi[MAX_N], mat[MAX_N][MAX_N];
vector<int> mpx, mpy;

int fpow(int bas, long long tim)
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

int ripe(vector<int> &src, int x) { return lower_bound(src.begin(), src.end(), x) - src.begin() + 1; }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        mpx.clear(), mpy.clear();
        scanf("%d%d%d%d", &h, &w, &m, &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d%d", &xp1[i], &yp1[i], &xp2[i], &yp2[i], &vi[i]);
            xp2[i]++, yp2[i]++;
            mpx.push_back(xp1[i]), mpx.push_back(xp2[i]), mpy.push_back(yp1[i]), mpy.push_back(yp2[i]);
        }
        mpx.push_back(1), mpy.push_back(1), mpx.push_back(h + 1), mpy.push_back(w + 1);
        sort(mpx.begin(), mpx.end()), mpx.erase(unique(mpx.begin(), mpx.end()), mpx.end());
        sort(mpy.begin(), mpy.end()), mpy.erase(unique(mpy.begin(), mpy.end()), mpy.end());
        for (int i = 1; i <= n; i++)
        {
            xp1[i] = ripe(mpx, xp1[i]), yp1[i] = ripe(mpy, yp1[i]);
            xp2[i] = ripe(mpx, xp2[i]), yp2[i] = ripe(mpy, yp2[i]);
        }
        int ans = 0, ux = mpx.size(), uy = mpy.size();
        for (int stat = 0; stat < (1 << n); stat++)
        {
            for (int i = 1; i < ux; i++)
                for (int j = 1; j < uy; j++)
                    mat[i][j] = m;
            for (int id = 1; id <= n; id++)
                for (int i = xp1[id]; i < xp2[id]; i++)
                    for (int j = yp1[id]; j < yp2[id]; j++)
                        mat[i][j] = min(mat[i][j], vi[id] - ((stat & (1 << (id - 1))) > 0));
            int opt = (mod + ((__builtin_popcount(stat) & 1) ? -1 : 1)) % mod;
            for (int i = 1; i < ux; i++)
                for (int j = 1; j < uy; j++)
                    opt = 1LL * opt * fpow(mat[i][j], 1LL * (mpx[i] - mpx[i - 1]) * (mpy[j] - mpy[j - 1])) % mod;
            ans = (0LL + ans + opt) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}