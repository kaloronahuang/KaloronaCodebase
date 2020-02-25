// BZ2811.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k, m, pre[MAX_N], suf[MAX_N], diff[MAX_N], lft[MAX_N], rig[MAX_N], num[MAX_N], pos[MAX_N], ltot;
int stot, ftot;

struct segment
{
    int l, r, c;
    bool operator<(const segment &rhs) const { return l < rhs.l || (l == rhs.l && r > rhs.r); }
} segs[MAX_N], rem[MAX_N], finalSet[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &segs[i].l, &segs[i].r, &segs[i].c);
        if (segs[i].c == 0)
            diff[segs[i].l]++, diff[segs[i].r + 1]--;
    }
    for (int i = 1; i <= n; i++)
        diff[i] += diff[i - 1];
    for (int i = 1; i <= n; i++)
        if (diff[i] == 0)
            lft[i] = rig[i] = num[i] = ++ltot, pos[ltot] = i;
    if (ltot == k)
    {
        for (int i = 1; i <= ltot; i++)
            printf("%d\n", pos[i]);
        return 0;
    }
    for (int i = 1; i <= n; i++)
        if (lft[i] == 0)
            lft[i] = lft[i - 1];
    for (int i = n; i >= 1; i--)
        if (rig[i] == 0)
            rig[i] = rig[i + 1];
    for (int i = 1; i <= m; i++)
        if (segs[i].c != 0)
        {
            int l = rig[segs[i].l], r = lft[segs[i].r];
            if (l <= r)
                rem[++stot] = segment{l, r, 1};
        }
    sort(rem + 1, rem + 1 + stot);
    for (int i = 1; i <= stot; i++)
    {
        while (ftot && finalSet[ftot].r >= rem[i].r)
            ftot--;
        finalSet[++ftot] = rem[i];
    }
    int range = 0;
    for (int i = 1; i <= ftot; i++)
        if (range < finalSet[i].l)
            pre[i] = pre[i - 1] + 1, range = finalSet[i].r;
        else
            pre[i] = pre[i - 1];
    range = 0x3f3f3f3f;
    for (int i = ftot; i >= 1; i--)
        if (range > finalSet[i].r)
            suf[i] = suf[i + 1] + 1, range = finalSet[i].l;
        else
            suf[i] = suf[i + 1];
    bool flag = false;
    for (int i = 1; i <= ftot; i++)
    {
        if (pre[i] != pre[i - 1] + 1)
            continue;
        if (finalSet[i].l == finalSet[i].r)
        {
            printf("%d\n", pos[finalSet[i].l]), flag = true;
            continue;
        }
        int ll = 0, rr = ftot + 1;
        int l = 1, r = i - 1;

        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (finalSet[mid].r < finalSet[i].r - 1)
                ll = mid, l = mid + 1;
            else
                r = mid - 1;
        }

        l = i + 1, r = ftot;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (finalSet[mid].l > finalSet[i].r - 1)
                rr = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (pre[ll] + suf[rr] + 1 > k)
            printf("%d\n", pos[finalSet[i].r]), flag = true;
    }
    if (flag == false)
        puts("-1");
    return 0;
}