// P2496.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_B = 330;

typedef long long ll;

int n, q, block, lft[MAX_B], rig[MAX_B], aff[MAX_N], btot, maxid[MAX_B];
ll ai[MAX_N], ki[MAX_B], bi[MAX_B];

void updateMax(int bid)
{
    maxid[bid] = lft[bid];
    for (int i = lft[bid]; i <= rig[bid]; i++)
        if (ai[i] + 1LL * ki[bid] * i + bi[bid] >= ai[maxid[bid]] + 1LL * ki[bid] * maxid[bid] + bi[bid])
            maxid[bid] = i;
}

void consolidate(int bid)
{
    if (ki[bid] == 0 && bi[bid] == 0)
        return;
    for (int i = lft[bid]; i <= rig[bid]; i++)
        ai[i] += 1LL * ki[bid] * i + bi[bid];
    ki[bid] = bi[bid] = 0, updateMax(bid);
}

void updateMove(int bid)
{
    while (maxid[bid] + 1 <= rig[bid] && 1LL * ki[bid] * (maxid[bid] + 1) + ai[maxid[bid] + 1] >= 1LL * ki[bid] * maxid[bid] + ai[maxid[bid]])
        maxid[bid]++;
}

int main()
{
    scanf("%d%d", &n, &q), block = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; i <= n; i += block)
    {
        lft[++btot] = i, rig[btot] = min(n, i + block - 1);
        for (int j = lft[btot]; j <= rig[btot]; j++)
            aff[j] = btot, maxid[btot] = (ai[maxid[btot]] <= ai[j]) ? j : maxid[btot];
    }
    while (q--)
    {
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            ll ans = 0;
            for (int i = aff[l] + 1; i <= aff[r] - 1; i++)
                ans = max(ans, 1LL * ki[i] * maxid[i] + bi[i] + ai[maxid[i]]);
            for (int i = l; i <= rig[aff[l]]; i++)
                ans = max(ans, 1LL * ki[aff[i]] * i + bi[aff[i]] + ai[i]);
            for (int i = r; i >= lft[aff[r]]; i--)
                ans = max(ans, 1LL * ki[aff[i]] * i + bi[aff[i]] + ai[i]);
            ll a1 = ai[1] + ki[1] + bi[1];
            printf("%lld\n", max(ans - a1, 0LL));
        }
        else if (opt == 2)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            consolidate(aff[l]), consolidate(aff[r]);
            swap(ai[l], ai[r]);
            updateMax(aff[l]), updateMax(aff[r]);
        }
        else
        {
            int l, r, t;
            scanf("%d%d%d", &l, &r, &t);
            for (int i = aff[l] + 1; i <= aff[r] - 1; i++)
                ki[i] += t, bi[i] += t - 1LL * t * l, updateMove(i);
            for (int i = l; i <= rig[aff[l]]; i++)
                ai[i] += 1LL * (i - l + 1) * t;
            for (int i = r; i >= lft[aff[r]]; i--)
                ai[i] += 1LL * (i - l + 1) * t;
            consolidate(aff[l]), consolidate(aff[r]);
        }
    }
    return 0;
}