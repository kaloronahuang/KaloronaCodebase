// P1645.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100;

struct segment
{
    int l, r, c;
    bool operator<(const segment &nd) const { return r < nd.r; }
} segs[MAX_N];

bool compare(segment &a, segment &b) { return a.l < b.l; }

int n, cnt[MAX_N], ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &segs[i].l, &segs[i].r, &segs[i].c);
    sort(segs + 1, segs + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = segs[i].l; j <= segs[i].r; j++)
            segs[i].c -= cnt[j], segs[i].c = max(segs[i].c, 0);
        if (segs[i].c > 0)
            for (int j = segs[i].r; j >= segs[i].l && segs[i].c > 0; j--)
                if (cnt[j] == 0)
                    ans++, cnt[j]++, segs[i].c--;
    }
    printf("%d", ans);
    return 0;
}