// CF1063D.cpp
#include <bits/stdc++.h>

using namespace std;

const int threshold = 2e6;

typedef long long ll;

ll n, l, r, k;

int main()
{
    scanf("%lld%lld%lld%lld", &n, &l, &r, &k);
    ll len = (r - l + n) % n + 1, ans = -1;
    if (n <= threshold)
        for (ll p = n; p >= 0; p--)
        {
            ll y = (k - 1) % (n + p) + 1 - len;
            if (y >= 0 && y <= min(p, len) && len - (y + 1) <= n - p)
            {
                ll y2 = y + 1;
                if (y2 <= p && y2 <= len)
                    ans = max(ans, p);
                if (len - y <= n - p)
                    ans = max(ans, p);
            }
        }
    else
    {
        if (k >= len && k <= (len << 1))
            ans = max(ans, k == (len << 1) ? n : n + k - (len << 1) + 1);
        for (ll i = 1; i <= k / n; i++)
        {
            ll s1 = max((k - (len << 1) + i - 1) / i, (k - len + n + i) / (i + 1));
            ll s2 = min((k - (len << 1) + (n << 1) + 1) / (i + 1), (k - len) / i);
            if (s1 <= s2)
                ans = max(s2 - n, ans);
        }
    }
    printf("%lld\n", ans);
    return 0;
}