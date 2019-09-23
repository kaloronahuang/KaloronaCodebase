// P2869.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

struct unit
{
    int p, q;
    bool operator<(const unit &un) const { return q > un.q; }
} grass[MAX_N], cow[MAX_N];

int n, m;

multiset<int> ms;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &cow[i].p, &cow[i].q);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &grass[i].p, &grass[i].q);
    sort(cow + 1, cow + 1 + n);
    sort(grass + 1, grass + 1 + m);
    ll ans = 0;
    for (int i = 1, j = 1; i <= n; i++)
    {
        while (j <= m && grass[j].q >= cow[i].q)
            ms.insert(grass[j++].p);
        auto it = ms.lower_bound(cow[i].p);
        ans += *it;
        ms.erase(it);
    }
    printf("%lld", ans);
    return 0;
}