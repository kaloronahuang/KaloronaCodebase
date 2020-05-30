// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, RANGE = 5e4, MAX_B = 230;

typedef long long ll;

int n, q, typ, ai[MAX_N], block_siz, cnt[MAX_B][MAX_N], aff[MAX_N], btot;
ll prod[MAX_B][MAX_B], lans, vis[MAX_N];

void clear(int l, int r)
{
    for (int k = l; k <= r; k++)
        vis[ai[k]] = 0;
}

ll calc(int l, int r, int bl, int br)
{
    ll ret = 0;
    for (int i = l; i <= r; i++)
    {
        if (!vis[ai[i]])
            vis[ai[i]] += cnt[br][ai[i]] - cnt[bl - 1][ai[i]];
        ret += vis[ai[i]], vis[ai[i]]++;
    }
    return ret;
}

ll getRect(int xl, int yl, int xr, int yr) { return prod[xr][yr] - prod[xl - 1][yr] - prod[xr][yl - 1] + prod[xl - 1][yl - 1]; }

int main()
{
    scanf("%d%d%d", &n, &q, &typ), block_siz = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), aff[i] = (i - 1) / block_siz + 1, cnt[aff[i]][ai[i]]++;
    btot = *max_element(aff + 1, aff + 1 + n);
    for (int i = 1; i <= btot; i++)
        for (int j = 1; j <= i; j++)
            if (i == j)
                for (int k = 1; k <= RANGE; k++)
                    prod[i][j] += 1LL * cnt[i][k] * (cnt[i][k] - 1) / 2;
            else
            {
                for (int k = (i - 1) * block_siz + 1; k <= min(n, i * block_siz); k++)
                    if (!vis[ai[k]])
                        vis[ai[k]] = 1, prod[i][j] += 1LL * cnt[i][ai[k]] * cnt[j][ai[k]];
                clear((i - 1) * block_siz + 1, min(i * block_siz, n));
            }
    for (int i = 1; i <= btot; i++)
        for (int j = 1; j <= RANGE; j++)
            cnt[i][j] += cnt[i - 1][j];
    for (int i = 1; i <= btot; i++)
        for (int j = 1; j <= btot; j++)
            prod[i][j] += prod[i - 1][j] + prod[i][j - 1] - prod[i - 1][j - 1];
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (typ)
            x ^= lans, y ^= lans;
        int l = min(x % n + 1, y % n + 1), r = max(x % n + 1, y % n + 1);
        lans = 0;
        if (aff[l] + 1 <= aff[r] - 1)
            lans += getRect(aff[l] + 1, aff[l] + 1, aff[r] - 1, aff[r] - 1);
        if (aff[l] == aff[r])
            lans += calc(l, r, 1, 0), clear(l, r);
        else
        {
            lans += calc(l, min(aff[l] * block_siz, n), aff[l] + 1, aff[r] - 1) + calc((aff[r] - 1) * block_siz + 1, r, aff[l] + 1, aff[r] - 1);
            clear(l, min(aff[l] * block_siz, n)), clear((aff[r] - 1) * block_siz + 1, r);
        }
        printf("%lld\n", lans);
    }
    return 0;
}