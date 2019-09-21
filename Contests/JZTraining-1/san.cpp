// san.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 42;

int n, h[MAX_N], g[MAX_N];
ll k;

vector<int> ht;
vector<ll> lft[MAX_N], rig[MAX_N];

void make_lft(int pos, int limit, ll sum)
{
    if (pos == n / 2)
    {
        int idx = lower_bound(ht.begin(), ht.end(), limit) - ht.begin();
        lft[idx].push_back(sum);
        return;
    }
    make_lft(pos + 1, limit, sum);
    if (h[pos] >= limit)
        make_lft(pos + 1, h[pos], sum + g[pos]);
}

void make_rig(int pos, int first, int limit, ll sum)
{
    if (pos == n)
    {
        int idx = lower_bound(ht.begin(), ht.end(), first) - ht.begin();
        rig[idx].push_back(sum);
        return;
    }
    make_rig(pos + 1, first, limit, sum);
    if (h[pos] >= limit)
    {
        int nfirst = (first == 0) ? h[pos] : first;
        make_rig(pos + 1, nfirst, h[pos], sum + g[pos]);
    }
}

int main()
{
    scanf("%d%lld", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &h[i], &g[i]);
        ht.push_back(h[i]);
    }
    ht.push_back(0), sort(ht.begin(), ht.end());
    make_lft(0, 0, 0);
    make_rig(n / 2, 0, 0, 0);
    ll ans = 0;
    for (int i = 0, siz = ht.size(); i < siz; i++)
        sort(rig[i].begin(), rig[i].end());
    for (int i = 0, siz = ht.size(); i < siz; i++)
        for (int j = 0, siz_ = lft[i].size(); j < siz_; j++)
        {
            int it = lft[i][j];
            ans += rig[0].end() - lower_bound(rig[0].begin(), rig[0].end(), k - it);
            for (int x = i, siz__ = ht.size(); x < siz__; x++)
                ans += rig[x].end() - lower_bound(rig[x].begin(), rig[x].end(), k - it);
        }
    printf("%lld\n", ans);
    return 0;
}