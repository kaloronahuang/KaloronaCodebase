// CF1249D2.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, k;
struct segment
{
    int first, second, id;
    bool operator<(const segment &sg) const { return first < sg.first; }
} segs[MAX_N];
multiset<pr> ms;
set<int> ans;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &segs[i].first, &segs[i].second), segs[i].id = i;
    sort(segs + 1, segs + 1 + n);
    int cur = 1, cnt = 0;
    for (int lpos = 0; lpos <= int(2e5); lpos++)
    {
        while (!ms.empty() && ms.begin()->first < lpos)
            ms.erase(ms.begin()), cnt--;
        while (cur <= n && segs[cur].first <= lpos)
        {
            cnt++;
            segment prs = segs[cur];
            ms.insert(make_pair(prs.second, prs.id));
            cur++;
        }
        while (cnt > k)
        {
            cnt--;
            multiset<pr>::iterator it = --ms.end();
            ans.insert(it->second), ms.erase(it);
        }
    }
    printf("%lld\n", 1LL * ans.size());
    while (!ans.empty())
        printf("%d ", *ans.begin()), ans.erase(ans.begin());
    return 0;
}