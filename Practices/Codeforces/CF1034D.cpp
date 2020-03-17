// CF1034D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

typedef pair<int, int> pii;
typedef long long ll;

int n, limit, li[MAX_N], ri[MAX_N], len[MAX_N];

struct node
{
    int l, r, timestamp;
    bool operator<(const node &rhs) const { return l < rhs.l || (l == rhs.l && r < rhs.r); }
};

multiset<node> ms;
vector<pii> info[MAX_N];

bool check(int mid)
{
    int acc = 0;
    ll cnt = 0;
    for (int i = 1, ptr = 1; i <= n; i++)
    {
        len[i] = ri[i] - li[i] + 1, acc += len[i];
        for (auto &x : info[i])
        {
            len[x.second] -= x.first;
            // coming later;
            if (x.second >= ptr)
                acc -= x.first;
        }
        while (acc >= mid)
            acc -= len[ptr], ptr++;
        cnt += ptr - 1;
    }
    return cnt >= limit;
}

void calc(int max_len)
{
    int acc = 0;
    ll ans = 0, len_acc = 0, len_cnt = 0;
    for (int i = 1, ptr = 1; i <= n; i++)
    {
        len[i] = ri[i] - li[i] + 1, acc += len[i];
        for (auto &x : info[i])
        {
            len[x.second] -= x.first;
            // coming later;
            if (x.second >= ptr)
                acc -= x.first;
            if (x.second > 0 && x.second < ptr)
                len_acc -= 1LL * x.second * x.first;
        }
        while (acc >= max_len)
            acc -= len[ptr], len_acc += 1LL * ptr * len[ptr], ptr++;
        ans += len_acc + 1LL * acc * (ptr - 1), len_cnt += (ptr - 1);
    }
    printf("%lld\n", ans - 1LL * (len_cnt - limit) * max_len);
}

int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &li[i], &ri[i]), ri[i]--;
    // ODT-like initialize;
    ms.insert(node{0, INF, 0});
    for (int i = 1; i <= n; i++)
    {
        auto it = --ms.lower_bound(node{li[i], INF, 0});
        if (it->r >= ri[i])
        {
            // covered;
            info[i].push_back(make_pair(ri[i] - li[i] + 1, it->timestamp));
            if (it->l < li[i])
                ms.insert(node{it->l, li[i] - 1, it->timestamp});
            if (it->r > ri[i])
                ms.insert(node{ri[i] + 1, it->r, it->timestamp});
            ms.erase(it), ms.insert(node{li[i], ri[i], i});
        }
        else
        {
            // intersect;
            info[i].push_back(make_pair(it->r - li[i] + 1, it->timestamp));
            if (it->l < li[i])
                ms.insert(node{it->l, li[i] - 1, it->timestamp});
            ms.erase(it++);
            if (it->r < li[i])
                it++;
            while (it->r < ri[i])
                info[i].push_back(make_pair(it->r - it->l + 1, it->timestamp)), ms.erase(it++);
            info[i].push_back(make_pair(ri[i] - it->l + 1, it->timestamp));
            if (it->r > ri[i])
                ms.insert(node{ri[i] + 1, it->r, it->timestamp});
            ms.erase(it), ms.insert(node{li[i], ri[i], i});
        }
    }
    int l = 0, r = 1e9, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    calc(res);
    return 0;
}