// grid.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T, n, m, x, y;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &n, &m, &x, &y);
        if (min(n, m) == 1)
            printf("%lld\n", 1LL * max(n - 1, m - 1) * x);
        else if (n == m)
            printf("%lld\n", min(1LL * (n - 1) * y, 1LL * (n + m - 2) * x));
        else if (2LL * x <= y)
            printf("%lld\n", 1LL * (n + m - 2) * x);
        else if (x <= y)
        {
            int rem = max(n - 1, m - 1) - min(n - 1, m - 1);
            ll ans = 1LL * y * min(n - 1, m - 1) + 1LL * rem * x;
            printf("%lld\n", ans);
        }
        else
        {
            int rem = max(n - 1, m - 1) - min(n - 1, m - 1);
            ll ans = 1LL * y * min(n - 1, m - 1) + 1LL * ((rem) >> 1) * (y << 1) + (rem & 1) * x;
            printf("%lld\n", ans);
        }
        /*
        long long ans = 1e18;
        ans = min(ans, 1LL * min(n - 1, m - 1) * y + 1LL * abs(n - m) * x);
        ans = min(ans, 1LL * (n + m - 2) * x);
        int block = min(n - 1, m - 1);
        int cnt = max(n - 1, m - 1) / block, rem = max(n - 1, m - 1) % block;
        if (cnt & 1)
            ans = min(ans, 1LL * y * cnt * min(n - 1, m - 1) + rem * x);
        else if (cnt > 0)
        {
            cnt--;
            ans = min(ans, 1LL * y * cnt * min(n - 1, m - 1) + (rem + min(n - 1, m - 1)) * x);
            cnt++;
            ans = min(ans, 1LL * y * (cnt + rem) * min(n - 1, m - 1) + (min(n - 1, m - 1) - rem) * x);
            ans = min(ans, 1LL * y * (cnt + rem) * min(n - 1, m - 1) + )
        }
        printf("%lld\n", ans);
        */
    }
    return 0;
}