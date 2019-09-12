// CF1207D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

pair<int, int> nodes[MAX_N];

int fac[MAX_N], n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].first, &nodes[i].second);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    int ans[4] = {fac[n], 1, 1, 1};
    for (int c = 1; c <= 2; c++)
    {
        sort(nodes + 1, nodes + 1 + n);
        int l = 1, r;
        while (l <= n)
        {
            r = l + 1;
            while (r <= n && nodes[r].first == nodes[l].first)
                r++;
            ans[c] = 1LL * ans[c] * fac[r - l] % mod;
            l = r;
        }
        ans[0] = (1LL * ans[0] + 1LL * (mod - ans[c])) % mod;
        for (int i = 1; i <= n; i++)
            swap(nodes[i].first, nodes[i].second);
    }
    int l = 1, r;
    sort(nodes + 1, nodes + 1 + n);
    while (l <= n)
    {
        r = l + 1;
        while (r <= n && nodes[r].first == nodes[l].first)
            r++;
        map<int, int> mp;
        mp.clear();
        for (int i = l; i < r; i++)
            mp[nodes[i].second]++;
        for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
            ans[3] = 1LL * ans[3] * fac[(*it).second] % mod;
        l = r;
    }
    for (int i = 2; i <= n; i++)
        if (nodes[i].second < nodes[i - 1].second)
            ans[3] = 0;
    ans[0] = (1LL * ans[0] + 1LL * ans[3]) % mod;
    printf("%d", ans[0]);
    return 0;
}