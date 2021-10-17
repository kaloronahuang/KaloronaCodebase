// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef pair<int, int> segment;
typedef long long ll;

int n, siz[MAX_N], btot;
segment segs[MAX_N];
vector<int> mp;
vector<int> cmp[MAX_N];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &segs[i].first, &segs[i].second), mp.push_back(segs[i].second);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end()), btot = mp.size();
    for (int i = 1; i <= n; i++)
        cmp[ripe(segs[i].second)].push_back(segs[i].first), siz[ripe(segs[i].second)]++;
    ll ans = 0;
    int lft = 0;
    for (int i = 1; i <= btot; i++)
        if (!cmp[i].empty())
        {
            cmp[i].push_back(lft);
            sort(cmp[i].begin(), cmp[i].end());
            lft = *cmp[i].rbegin();
        }
    for (int i = 1; i <= btot; i++)
        if (siz[i] != 0)
            ans += 1LL * siz[i] * (*cmp[i].rbegin());
    printf("%lld\n", ans);
    return 0;
}