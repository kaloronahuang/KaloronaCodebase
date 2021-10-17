// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int T, n, cntx[MAX_N], cnty[MAX_N], prefix1[MAX_N];
ll dp1[MAX_N], dp2[MAX_N];
pii pts[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            cntx[i] = cnty[i] = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &pts[i].first, &pts[i].second), cntx[pts[i].first]++, cnty[pts[i].second]++;
        ll ans = 0;
        // Case 1:
        for (int i = 1; i <= n; i++)
            prefix1[i] = prefix1[i - 1] + cntx[i];
        for (int i = 1; i <= n; i++)
            dp1[i] = 1LL * prefix1[i - 1] * cntx[i] + dp1[i - 1];
        for (int i = 1; i <= n; i++)
            dp2[i] = 1LL * cntx[i] * dp1[i - 1], ans += dp2[i];
        // Case 2:
        for (int i = 1; i <= n; i++)
            ans += 1LL * (prefix1[i - 1] + prefix1[n] - prefix1[i]) * ((1LL * (cntx[i] - 1) * cntx[i]) >> 1);
        for (int i = 1; i <= n; i++)
            ans -= 1LL * (cntx[pts[i].first] - 1) * (cnty[pts[i].second] - 1);
        // Case 3:
        for (int i = 1; i <= n; i++)
            if (cntx[i] >= 3)
                ans += ((1LL * cntx[i] * (cntx[i] - 1)) >> 1) * (cntx[i] - 2) / 3;
        printf("%lld\n", ans);
    }
    return 0;
}