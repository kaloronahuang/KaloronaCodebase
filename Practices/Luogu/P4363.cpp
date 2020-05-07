// P4363.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 15, base = 12;

typedef unsigned long long ll;

int n, m, ai[MAX_N][MAX_N], bi[MAX_N][MAX_N], org[MAX_N];
map<ll, int> mp;

ll encode()
{
    ll ret = 0;
    for (int i = 1; i <= n; i++)
        ret = ret * base + org[i];
    return ret;
}

void decode(ll stat)
{
    for (int i = n; i >= 1; i--)
        org[i] = stat % base, stat /= base;
}

int sgn()
{
    int ret = 0;
    for (int i = 1; i <= n; i++)
        ret += org[i];
    return ret & 1;
}

int dfs(ll stat)
{
    if (mp.count(stat) != 0)
        return mp[stat];
    decode(stat);
    int opt = sgn(), ret = opt ? 0x3f3f3f3f : -0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        if (org[i - 1] > org[i])
        {
            org[i]++;
            ll nxt = encode();
            if (opt)
                ret = min(ret, dfs(nxt) - bi[i][org[i]]);
            else
                ret = max(ret, dfs(nxt) + ai[i][org[i]]);
            org[i]--;
        }
    return mp[stat] = ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &ai[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &bi[i][j]);
    for (int i = 0; i <= n; i++)
        org[i] = m;
    mp[encode()] = 0;
    printf("%d\n", dfs(0));
    return 0;
}