// CF940F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, block = 2154;

int n, q, ai[MAX_N], bucket[MAX_N], cnt[MAX_N], ans[MAX_N], qtot, mtot, lft, rig;
vector<int> mp;
bool tag[MAX_N];

struct queryInfo
{
    int l, r, p, x, id, bef;
    bool operator<(const queryInfo &rhs) const { return l / block < rhs.l / block || (l / block == rhs.l / block && (r / block < rhs.r / block || (r / block == rhs.r / block && bef < rhs.bef))); }
} queries[MAX_N], mod[MAX_N];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

void add(int x)
{
    if (cnt[x] >= 0)
        --bucket[cnt[x]];
    if (++cnt[x] >= 0)
        ++bucket[cnt[x]];
}

void remove(int x)
{
    if (cnt[x] >= 0)
        --bucket[cnt[x]];
    if (--cnt[x] >= 0)
        ++bucket[cnt[x]];
}

void modify(int cid, int qid)
{
    if (queries[qid].l <= mod[cid].p && mod[cid].p <= queries[qid].r)
    {
        remove(ai[mod[cid].p]);
        add(mod[cid].x);
    }
    swap(ai[mod[cid].p], mod[cid].x);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mp.push_back(ai[i]);
    for (int i = 1, opt; i <= q; i++)
    {
        scanf("%d", &opt);
        if (opt == 1)
            qtot++, scanf("%d%d", &queries[qtot].l, &queries[qtot].r), queries[qtot].id = i, queries[qtot].bef = mtot, tag[i] = true;
        else
            mtot++, scanf("%d%d", &mod[mtot].p, &mod[mtot].x), mp.push_back(mod[mtot].x), mod[mtot].id = i;
    }
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        ai[i] = ripe(ai[i]);
    for (int i = 1; i <= mtot; i++)
        mod[i].x = ripe(mod[i].x);
    sort(queries + 1, queries + 1 + qtot);
    lft = 1, rig = 0;
    int ptr = 0;
    for (int i = 1; i <= qtot; i++)
    {
        while (lft > queries[i].l)
            add(ai[--lft]);
        while (rig < queries[i].r)
            add(ai[++rig]);
        while (lft < queries[i].l)
            remove(ai[lft++]);
        while (rig > queries[i].r)
            remove(ai[rig--]);
        while (ptr < queries[i].bef)
            modify(++ptr, i);
        while (ptr > queries[i].bef)
            modify(ptr--, i);
        ans[queries[i].id] = 1;
        while (bucket[ans[queries[i].id]] > 0)
            ans[queries[i].id]++;
    }
    for (int i = 1; i <= q; i++)
        if (tag[i])
            printf("%d\n", ans[i]);
    return 0;
}