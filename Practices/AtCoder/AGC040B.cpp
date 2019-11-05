// AGC040B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

struct segment
{
    int l, r;
    bool operator<(const segment &nd) const { return r < nd.r; }
} segs[MAX_N];

int n;
multiset<int> ms;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &segs[i].l, &segs[i].r);
    sort(segs + 1, segs + 1 + n);
    int lft = segs[1].l, rig = segs[1].r, gans = 0;
    for (int i = 2; i <= n; i++)
        ms.insert(segs[i].l);
    for (int i = 2; i <= n - 1; i++)
    {
        int grig = segs[i].r;
        ms.erase(ms.find(segs[i].l));
        // calc;
        int L1 = *ms.begin(), L2 = *ms.rbegin();
        int pans = max(grig - max(L1, segs[i].l) + 1, 0) + max(rig - max(lft, L2) + 1, 0);
        pans = max(pans, max(grig - max(L2, segs[i].l) + 1, 0) + max(rig - max(lft, L1) + 1, 0));
        pans = max(pans, max(grig - max(L2, segs[i].l) + 1, 0) + max(rig - lft + 1, 0));
        pans = max(pans, max(grig - segs[i].l + 1, 0) + max(rig - max(lft, L2) + 1, 0));
        gans = max(gans, pans);
        // merge;
        lft = max(lft, segs[i].l), rig = min(rig, segs[i].r);
    }
    gans = max(gans, max(rig - lft + 1, 0) + max(segs[n].r - segs[n].l + 1, 0));
    printf("%d", gans);
    return 0;
}
