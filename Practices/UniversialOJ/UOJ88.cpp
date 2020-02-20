// UOJ88.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, INF = 0x3f3f3f3f;

typedef long long ll;

int n, m, queries[MAX_N], qtot;
vector<pair<int, int> /**/> rate[MAX_N];
char cmdlet[20];
vector<int> mp;

struct node
{
    int l, r;
    ll k, b;

    ll query(ll x) { return 1LL * k * x + b; }
} mx[MAX_N << 2], mi[MAX_N << 2];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int raw(int x) { return mp[x - 1]; }

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

ll query(int qx, int l, int r, int p)
{
    ll mx_ans = abs(mx[p].query(raw(qx))), mi_ans = abs(mi[p].query(raw(qx)));
    if (l == r)
        return max(mx_ans, mi_ans);
    ll ans = 0;
    if (qx <= mid)
        ans = query(qx, l, mid, lson);
    else
        ans = query(qx, mid + 1, r, rson);
    return max(ans, max(mx_ans, mi_ans));
}

void update_max(int l, int r, int p, node val)
{
    if (val.query(raw(mid)) > mx[p].query(raw(mid)))
        swap(mx[p], val);
    if (l == r)
        return;
    // judge if this is completely covered;
    if (min(mx[p].query(raw(l)), mx[p].query(raw(r))) >= max(val.query(raw(l)), val.query(raw(r))))
        return;
    if (val.k < mx[p].k)
        update_max(l, mid, lson, val);
    else
        update_max(mid + 1, r, rson, val);
}

void update_min(int l, int r, int p, node val)
{
    if (val.query(raw(mid)) < mi[p].query(raw(mid)))
        swap(mi[p], val);
    if (l == r)
        return;
    if (max(mi[p].query(raw(l)), mi[p].query(raw(r))) <= min(val.query(raw(l)), val.query(raw(r))))
        return;
    if (val.k >= mi[p].k)
        update_min(l, mid, lson, val);
    else
        update_min(mid + 1, r, rson, val);
}

void insert(int l, int r, int p, node val)
{
    if (val.l <= l && r <= val.r)
    {
        update_max(l, r, p, val), update_min(l, r, p, val);
        return;
    }
    if (val.l <= mid)
        insert(l, mid, lson, val);
    if (mid < val.r)
        insert(mid + 1, r, rson, val);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &m);
    mp.push_back(0);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), rate[i].push_back(make_pair(0, val));
    for (int i = 1, ti, id, x; i <= m; i++)
    {
        scanf("%d%s", &ti, cmdlet + 1), mp.push_back(ti);
        if (cmdlet[1] == 'c')
            scanf("%d%d", &id, &x), rate[id].push_back(make_pair(ti, x));
        else
            queries[++qtot] = ti;
    }
    mp.push_back(INF);
    for (int i = 1; i <= n; i++)
        rate[i].push_back(make_pair(INF, 0));
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    int upper = mp.size();
    for (int rid = 1, siz = rate[rid].size(); rid <= n; rid++, siz = rate[rid].size())
    {
        ll acc = rate[rid][0].second;
        node p = node{ripe(rate[rid][0].first), ripe(rate[rid][1].first), 0, acc};
        insert(1, upper, 1, p);
        for (int i = 1; i < siz - 1; i++)
        {
            // rate[rid][i] & rate[rid][i + 1];
            p = node{ripe(rate[rid][i].first), ripe(rate[rid][i + 1].first), rate[rid][i].second, acc - 1LL * rate[rid][i].second * rate[rid][i].first};
            insert(1, upper, 1, p), acc += 1LL * rate[rid][i].second * (rate[rid][i + 1].first - rate[rid][i].first);
        }
    }
    for (int i = 1; i <= qtot; i++)
        printf("%lld\n", query(ripe(queries[i]), 1, upper, 1));
    return 0;
}