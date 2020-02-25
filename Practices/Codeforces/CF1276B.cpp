// CF1276B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int T, n, m, A, B, ui[MAX_N], vi[MAX_N];

struct DSU
{
    int mem[MAX_N];

    void clear()
    {
        for (int i = 1; i <= n; i++)
            mem[i] = i;
    }

    int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }
} dsu[2];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &n, &m, &A, &B), dsu[0].clear(), dsu[1].clear();
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &ui[i], &vi[i]);
        vector<pii> aff;
        for (int i = 1; i <= m; i++)
        {
            if (ui[i] != A && vi[i] != A)
                dsu[0].mem[dsu[0].find(ui[i])] = dsu[0].find(vi[i]);
            if (ui[i] != B && vi[i] != B)
                dsu[1].mem[dsu[1].find(ui[i])] = dsu[1].find(vi[i]);
        }
        for (int i = 1; i <= n; i++)
            if (i != A && i != B)
                aff.push_back(make_pair(dsu[0].find(i), dsu[1].find(i)));
        ll ans = 1LL * aff.size() * (aff.size() - 1) / 2;
        map<int, int> mp;
        for (auto x : aff)
            mp[x.first]++;
        for (auto x : mp)
            ans -= 1LL * x.second * (x.second - 1) / 2;
        mp.clear();
        for (auto x : aff)
            mp[x.second]++;
        for (auto x : mp)
            ans -= 1LL * x.second * (x.second - 1) / 2;
        map<pii, int> pmp;
        for (auto x : aff)
            pmp[x]++;
        for (auto x : pmp)
            ans += 1LL * x.second * (x.second - 1) / 2;
        printf("%lld\n", ans);
    }
    return 0;
}