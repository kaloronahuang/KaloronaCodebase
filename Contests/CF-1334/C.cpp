// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200;

typedef long long ll;

int T, n;
ll ai[MAX_N], bi[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        ll tot = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld%lld", &ai[i], &bi[i]), tot += ai[i], ai[i + n] = ai[i], bi[i + n] = bi[i];
        ai[n + n + 1] = bi[n + n + 1] = 0;
        for (int i = n << 1; i >= 1; i--)
            bi[i] = min(bi[i], ai[i % (n << 1) + 1]);
        for (int i = n << 1; i >= 1; i--)
            ai[i] += ai[i + 1], bi[i] += bi[i + 1];
        ll ans = 1e18;
        for (int i = 1; i <= n; i++)
            ans = min(ans, tot - (bi[i] - bi[i + n - 1]));
        printf("%lld\n", ans);
    }
    return 0;
}