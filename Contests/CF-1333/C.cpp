// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, ai[MAX_N], lft[MAX_N];
ll pre[MAX_N], ans;
map<ll, int> mp;

int main()
{
    memset(lft, -1, sizeof(lft));
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pre[i] = pre[i - 1] + ai[i];
    mp[0] = 0;
    int lft_bd = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mp.count(pre[i]))
            lft[i] = mp[pre[i]];
        mp[pre[i]] = i, lft_bd = max(lft_bd, lft[i] + 1);
        ans += i - lft_bd;
    }
    printf("%lld\n", ans);
    return 0;
}