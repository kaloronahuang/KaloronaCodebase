// CF1314A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, ai[MAX_N], ti[MAX_N];
map<int, multiset<int> /**/> mp;
ll ans, sum;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ti[i]);
        mp[ai[i]].insert(ti[i]);
    }
    // printf("%lld\n", mp.size()), fflush(stdout);
    int current_place = 0;
    multiset<int> pre_stat;
    while (!mp.empty() || !pre_stat.empty())
    {
        if (mp.count(current_place))
        // insert the fresh stuff;
        {
            for (auto x : mp[current_place])
                pre_stat.insert(x), sum += x;
            mp.erase(mp.find(current_place));
        }
        if (pre_stat.empty())
        {
            current_place = mp.begin()->first, pre_stat = mp.begin()->second;
            mp.erase(mp.begin());
            for (auto x : pre_stat)
                sum += x;
        }
        // placer;
        int curt = *pre_stat.rbegin();
        sum -= curt, pre_stat.erase(--pre_stat.end());
        ans += sum, current_place++;
    }
    printf("%lld\n", ans);
    return 0;
}