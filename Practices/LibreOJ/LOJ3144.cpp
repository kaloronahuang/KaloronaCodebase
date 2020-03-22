// LOJ3144.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 200;

ll n, A, B, loop, cnt;
pair<ll, ll> segs[MAX_N << 1];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%lld%lld%lld", &n, &A, &B);
    loop = A / gcd(A, B + 1) * B;
    for (int i = 1; i <= n; i++)
    {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        if (r - l + 1 >= loop)
            printf("%lld\n", loop), exit(0);
        l %= loop, r %= loop;
        if (l <= r)
            segs[++cnt] = make_pair(l, r);
        else
            segs[++cnt] = make_pair(l, loop - 1), segs[++cnt] = make_pair(0, r);
    }
    sort(segs + 1, segs + 1 + cnt);
    segs[++cnt] = make_pair(loop + 1, 0);
    ll lft = segs[1].first, rig = segs[1].second, ans = 0;
    for (int i = 2; i <= cnt; i++)
    {
        if (rig < segs[i].first)
        {
            ans += rig - lft + 1;
            lft = segs[i].first, rig = segs[i].second;
        }
        else
            rig = max(rig, segs[i].second);
    }
    printf("%lld\n", ans);
    return 0;
}