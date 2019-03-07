// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 1000;
struct cas
{
    ll x, y, z;
    bool operator<(const cas &cs) const { return x < cs.x || (cs.x == x && y < cs.y) || (y == cs.y && x == cs.x && z < cs.z); }
} cases[MAX_N];
ll n, ans1, ans2, ans3, ans;
int main()
{
    freopen("psy.in", "r", stdin);
    freopen("psy.out", "w", stdout);
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld", &cases[i].x, &cases[i].y, &cases[i].z);
        ans1 = max(ans1, cases[i].x), ans2 = max(ans2, cases[i].y), ans3 = max(ans3, cases[i].z);
    }
    ans = min(ans1, min(ans2, ans3));
    sort(cases + 1, cases + 1 + n);
    ll l = 0, r = n, l1 = 0, r1 = n;
    while (l < r)
    {
        ll mid = (l + r) >> 1;
        l1 = 0, r1 = n;
        bool flag = true;
        while (l1 < r1)
        {
            ll mid1 = (l1 + r1) >> 1;
            if (mid1 == mid)
                if (mid1 + 1 <= r)
                    mid1++;
                else if (mid1 - 1 >= l)
                    mid1--;
                else
                {
                    flag = false;
                    break;
                }
            ll k = 0;
            for (int i = 1; i <= n; i++)
            {
                if (cases[i].x <= cases[mid].x)
                    continue;
                if (cases[i].y <= cases[mid1].y)
                    continue;
                if (cases[i].z > k)
                    k = cases[i].z;
            }
            ans1 = cases[mid].x + cases[mid1].y + k;
            if (ans1 < ans)
                ans = ans1, flag = true, r1 = mid1;
            else
                l1 = mid1 + 1;
        }
        if (flag)
            r = mid;
        else
            l = mid + 1;
    }
    ll k = 0;
    for (int i = 1; i <= n; i++)
    {
        if (cases[i].x <= cases[l].x)
            continue;
        if (cases[i].y <= cases[l1].y)
            continue;
        if (cases[i].z > k)
            k = cases[i].z;
    }
    ans = min(ans, cases[l].x + cases[l1].y + k);
    printf("%lld", ans);
    return 0;
}