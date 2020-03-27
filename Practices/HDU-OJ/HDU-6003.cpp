// HDU-6003.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, m, pts[MAX_N];

struct segment
{
    int l, r;
    bool operator<(const segment &rhs) const { return r > rhs.r; }
} segs[MAX_N];

int main()
{
    int caseTot = 0;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &segs[i].l, &segs[i].r);
        for (int i = 1; i <= m; i++)
            scanf("%d", &pts[i]);
        sort(segs + 1, segs + 1 + n, [](const segment &rhs1, const segment &rhs2) { return rhs1.l < rhs2.l || (rhs1.l == rhs2.l && rhs1.r > rhs2.r); });
        sort(pts + 1, pts + 1 + m);
        priority_queue<segment> pq;
        int ans = 0, ptr = 0;
        for (int i = 1; i <= m; i++)
        {
            while (ptr < n && segs[ptr + 1].l <= pts[i])
                ptr++, pq.push(segs[ptr]);
            while (!pq.empty() && pq.top().r < pts[i])
                pq.pop();
            ans = max(ans, int(n - pq.size() + 1));
            if (!pq.empty())
                pq.pop();
        }
        caseTot++;
        printf("Case #%d: ", caseTot);
        if (ans > n)
            puts("IMPOSSIBLE!");
        else
            printf("%d\n", ans);
    }
    return 0;
}