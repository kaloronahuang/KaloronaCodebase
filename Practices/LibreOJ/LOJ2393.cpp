// LOJ2393.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;
typedef pair<int, ll> pil;

int n, m;
ll ai[MAX_N], bi[MAX_N];
vector<pil> tags[MAX_N];

struct segment
{
    int l, r, c;
} segs[MAX_N];

bool judge(ll threshold, int pos, ll rev_cnt)
{
    if (threshold < rev_cnt)
        return false;
    priority_queue<pil> pq;
    for (int i = 1; i <= n; i++)
        bi[i] = 0, tags[i].clear();
    for (int i = 1; i <= m; i++)
        if (segs[i].l <= pos && pos < segs[i].r)
            tags[segs[i].l].push_back(make_pair(segs[i].r, segs[i].c));
    ll curt = 0;
    for (int i = 1; i <= pos; i++)
    {
        for (pil v : tags[i])
            pq.push(v);
        while (ai[i] - curt + rev_cnt > threshold)
        {
            if (pq.empty())
                return false;
            pil u = pq.top();
            pq.pop();
            ll crev = min(u.second, (ai[i] - curt + rev_cnt - threshold + 1) >> 1);
            curt += crev, rev_cnt -= crev, bi[u.first] += (crev << 1);
            if (u.second != crev)
                pq.push(make_pair(u.first, u.second - crev));
        }
    }
    bi[pos + 1] -= curt;
    for (int i = pos + 1; i <= n; i++)
    {
        bi[i] += bi[i - 1];
        if (bi[i] + ai[i] > threshold)
            return false;
    }
    return true;
}

bool check(ll threshold, int pos)
{
    return judge(threshold, pos, ai[pos] - threshold) || judge(threshold, pos, ai[pos] - threshold + 1);
}

int main()
{
    // freopen("02-06.in", "r", stdin);
    scanf("%d%d", &n, &m);
    ll l = 0, r = 0, res = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &segs[i].l, &segs[i].r, &segs[i].c);
        if (segs[i].l > segs[i].r)
            swap(segs[i].l, segs[i].r);
        ai[segs[i].l] += segs[i].c, ai[segs[i].r] -= segs[i].c;
        r += segs[i].c;
    }
    for (int i = 1; i <= n; i++)
        ai[i] += ai[i - 1];
    int lpt = 0, rpt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (ai[i] > ai[lpt] || lpt == 0)
            lpt = i;
        if (ai[i] >= ai[rpt])
            rpt = i;
    }
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid, lpt) || check(mid, rpt))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", res);
    return 0;
}