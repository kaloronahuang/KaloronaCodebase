// B.cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MAX_N = 5e5 + 200;

ll seq[MAX_N], n, lft[MAX_N], rig[MAX_N];
vector<ll> vec;

void sixty_pts()
{
    ll mx_val = 0;
    for (ll i = 1; i <= n; i++)
    {
        ll cur = i;
        while (cur >= 2 && seq[cur - 1] % seq[i] == 0)
            cur--;
        lft[i] = cur;
        cur = i;
        while (cur < n && seq[cur + 1] % seq[i] == 0)
            cur++;
        rig[i] = cur;
        mx_val = max(mx_val, rig[i] - lft[i]);
        if (mx_val == n - 1)
            break;
    }
    for (ll i = 1; i <= n; i++)
        if (rig[i] - lft[i] == mx_val)
            vec.push_back(lft[i]);
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    printf("%lld %lld\n", vec.size(), mx_val);
    for (vector<ll>::iterator it = vec.begin(); it != vec.end(); it++)
        printf("%lld ", *it);
}

int main()
{
    /*
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);
    */
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    sixty_pts();
    return 0;
}
