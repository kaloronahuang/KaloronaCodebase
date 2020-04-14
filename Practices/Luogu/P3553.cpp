// P3553.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

using namespace std;

int T, n, m, tot[MAX_N], st[MAX_N], ed[MAX_N];

struct record
{
    int time_frame, pid, rest_tot;
    bool operator<(const record &rhs) const { return time_frame < rhs.time_frame; }
} recs[MAX_N];

struct segment
{
    int l, r;
    bool operator<(const segment &rhs) const { return l > rhs.l || (l == rhs.l && r < rhs.r); }
} segs[MAX_N];

inline char nc()
{
    static char buffer[1 << 20], *p1 = buffer, *p2 = buffer;
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = nc();
    }
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

bool check(int mid)
{
    for (int i = 1; i <= m; i++)
        tot[i] = st[i] = ed[i] = 0;
    for (int i = 1; i <= n; i++)
        segs[i].l = INF, segs[i].r = -INF;
    for (int i = 1; i <= mid; i++)
    {
        segs[recs[i].pid].l = min(segs[recs[i].pid].l, recs[i].time_frame), segs[recs[i].pid].r = max(segs[recs[i].pid].r, recs[i].time_frame);
        if (tot[recs[i].time_frame] != 0 && recs[i].rest_tot + 1 != tot[recs[i].time_frame])
            return false;
        tot[recs[i].time_frame] = recs[i].rest_tot + 1;
    }
    for (int i = 1; i <= n; i++)
        if (segs[i].l != INF)
            st[segs[i].l]++, ed[segs[i].r]++;
    int req = 0, curt = 0, finished = 0, unfinished = 0;
    for (int i = 1; i <= m; i++)
        if (tot[i])
        {
            curt += st[i];
            if (curt > tot[i])
                return false;
            if (st[i] <= unfinished)
                unfinished -= st[i];
            else
                req += st[i] - unfinished, unfinished = 0;
            if (curt + finished + unfinished < tot[i])
                req += tot[i] - (curt + finished + unfinished), unfinished = tot[i] - curt - finished;
            else
            {
                if (curt + unfinished > tot[i])
                    unfinished = tot[i] - curt, finished = 0;
                else
                    finished = tot[i] - curt - unfinished;
            }
            curt -= ed[i], finished += ed[i];
        }
    if (req > n)
        return false;
    return true;
}

int main()
{
    T = read();
    while (T--)
    {
        n = read(), m = read();
        for (int i = 1; i <= m; i++)
            recs[i].time_frame = read(), recs[i].pid = read(), recs[i].rest_tot = read();
        int l = 0, r = m, res;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                l = mid + 1, res = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", res);
    }
    return 0;
}