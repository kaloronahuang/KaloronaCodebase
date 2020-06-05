// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_B = 260;

typedef pair<int, int> pii;
typedef long long ll;

int n, q, ai[MAX_N], block_siz, btot, aff[MAX_N];
pii d[MAX_N];

void unique(pii *arr, int &siz)
{
    int ret = 0;
    for (int i = 1; i <= siz; i++)
        if (i == siz || arr[i].first > arr[i + 1].first)
            arr[++ret] = arr[i];
    siz = ret;
}

struct block
{
    int len, lft, rig, ansBox[MAX_B], pt, st, gen;
    pii pre[40], suf[40];

    void initialize(int l, int r) { lft = l, rig = r, len = r - l + 1; }

    void maintain()
    {
        pt = 0, st = 0;
        for (int i = lft; i <= rig; i++)
        {
            for (int j = 1; j <= st; j++)
                suf[j].first |= ai[i];
            suf[++st] = make_pair(ai[i], i);
            unique(suf, st);
            for (int j = 1; j <= st; j++)
                ansBox[i - suf[j].second + 1] = max(ansBox[i - suf[j].second + 1], suf[j].first);
        }
        for (int i = 2; i <= len; i++)
            ansBox[i] = max(ansBox[i], ansBox[i - 1]);
        for (int i = lft; i <= rig; i++)
            if (pt == 0 || (pre[pt].first | ai[i]) > pre[pt].first)
                pre[pt + 1] = make_pair(pre[pt].first | ai[i], i - lft + 1), pt++;
        gen = pre[pt].first;
    }
} bks[MAX_B];

int main()
{
    scanf("%d%d", &n, &q), block_siz = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i += block_siz)
    {
        int l = i, r = min(i + block_siz - 1, n);
        bks[++btot].initialize(l, r), bks[btot].maintain();
        for (int j = l; j <= r; j++)
            aff[j] = btot;
    }
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            scanf("%d", &y), ai[x] = y, bks[aff[x]].maintain();
        else
        {
            int ans = n + 1, dtot = 0;
            for (int i = 1; i <= btot; i++)
                while (ans && bks[i].ansBox[min(ans - 1, bks[i].len)] >= x)
                    ans = min(ans - 1, bks[i].len);
            for (int i = 1; i <= btot; i++)
            {
                int chain_ptr = 1;
                for (int j = 1; j <= bks[i].pt; j++)
                    for (; chain_ptr <= dtot && (bks[i].pre[j].first | d[chain_ptr].first) >= x; chain_ptr++)
                        ans = min(ans, i * block_siz - block_siz + 1 + bks[i].pre[j].second - d[chain_ptr].second);
                for (int j = 1; j <= dtot; j++)
                    d[j].first |= bks[i].gen;
                for (int j = 1; j <= bks[i].st; j++)
                    d[++dtot] = bks[i].suf[j];
                unique(d, dtot);
            }
            printf("%d\n", ans > n ? -1 : ans);
        }
    }
    return 0;
}