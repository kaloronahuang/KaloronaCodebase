// UOJ386.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, m, ds, dv, lft[MAX_N], rig[MAX_N], idx[MAX_N];
ll prefix[MAX_N];

struct node
{
    int siz, stick;
    bool operator<(const node &rhs) const { return siz < rhs.siz; }
} nodes[MAX_N];

ll calcS(ll x) { return ds == 1 ? x : x * x; }

ll calcV(ll x) { return dv == 1 ? x : x * x; }

int main()
{
    scanf("%d%d%d%d", &n, &m, &ds, &dv);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].siz, &nodes[i].stick);
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + nodes[i].stick;
    ll ans = 0;
    for (int len = 1; len < m; len++)
        for (int i = 1; i + len - 1 <= n; i++)
            ans = max(ans, calcV(prefix[i + len - 1] - prefix[i - 1]) - calcS(nodes[i + len - 1].siz - nodes[i].siz));
    for (int i = 1; i <= n; i++)
        lft[i] = i - 1, rig[i] = i + 1, idx[i] = i;
    rig[n] = 0;
    sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return nodes[rhs1].stick < nodes[rhs2].stick; });
    for (int i = 1; i <= n; i++)
    {
        int u = idx[i];
        vector<int> vec;
        for (int len = 1, ptr = lft[u]; len < m && ptr; len++, ptr = lft[ptr])
            vec.push_back(ptr);
        reverse(vec.begin(), vec.end()), vec.push_back(u);
        for (int len = 1, ptr = rig[u]; len < m && ptr; len++, ptr = rig[ptr])
            vec.push_back(ptr);
        for (int j = 1, siz = vec.size(); j <= siz; j++)
            prefix[j] = prefix[j - 1] + nodes[vec[j - 1]].stick;
        for (int j = 1, siz = vec.size(); j + m - 1 <= siz; j++)
            ans = max(ans, calcV(prefix[j + m - 1] - prefix[j - 1]) - calcS(nodes[vec[j + m - 1 - 1]].siz - nodes[vec[j - 1]].siz));
        rig[lft[u]] = rig[u], lft[rig[u]] = lft[u];
    }
    printf("%lld\n", ans);
    return 0;
}