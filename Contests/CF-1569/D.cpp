// D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int MAX_N = 5e5 + 200;

int T, n, m, k, xi[MAX_N], yi[MAX_N];
pii pts[MAX_N];
vector<int> bucx, bucy;
map<int, bool> markx, marky;
map<int, int> cntx, cnty;
map<pii, int> ptcnt;

int ripe(vector<int> &bucket, int x) { return lower_bound(bucket.begin(), bucket.end(), x) - bucket.begin() + 1; }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        bucx.clear(), bucy.clear();
        markx.clear(), marky.clear(), cntx.clear(), cnty.clear(), ptcnt.clear();
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &xi[i]), bucx.push_back(xi[i]);
        for (int i = 1; i <= m; i++)
            scanf("%d", &yi[i]), bucy.push_back(yi[i]);
        sort(xi + 1, xi + 1 + n), sort(yi + 1, yi + 1 + m);

        for (int i = 1; i <= n; i++)
            bucx.push_back(xi[i] - 1);
        bucx.push_back(xi[n] + 1);

        for (int i = 1; i <= m; i++)
            bucy.push_back(yi[i] - 1);
        bucy.push_back(yi[m] + 1);

        for (int i = 1; i <= k; i++)
            scanf("%d%d", &pts[i].first, &pts[i].second);
        sort(bucx.begin(), bucx.end()), bucx.erase(unique(bucx.begin(), bucx.end()), bucx.end());
        sort(bucy.begin(), bucy.end()), bucy.erase(unique(bucy.begin(), bucy.end()), bucy.end());

        for (int i = 1; i <= n; i++)
            xi[i] = ripe(bucx, xi[i]);
        for (int i = 1; i <= m; i++)
            yi[i] = ripe(bucy, yi[i]);
        for (int i = 1; i <= k; i++)
            pts[i].first = ripe(bucx, pts[i].first), pts[i].second = ripe(bucy, pts[i].second);

        for (int i = 1; i <= n; i++)
            markx[xi[i]] = true;
        for (int i = 1; i <= m; i++)
            marky[yi[i]] = true;
        for (int i = 1; i <= k; i++)
            cntx[pts[i].first]++, cnty[pts[i].second]++, ptcnt[pts[i]]++;
        ll ans = 0;
        for (pair<pii, int> u : ptcnt)
        {
            if (!markx.count(u.first.first))
                ans += 1LL * (cntx[u.first.first] - u.second) * u.second;
            if (!marky.count(u.first.second))
                ans += 1LL * (cnty[u.first.second] - u.second) * u.second;
        }
        printf("%lld\n", ans >> 1);
    }
    return 0;
}