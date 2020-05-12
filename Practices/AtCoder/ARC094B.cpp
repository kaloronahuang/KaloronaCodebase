// ARC094B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll Q, n = 1e12, a, b;

int main()
{
    scanf("%lld", &Q);
    while (Q--)
    {
        scanf("%lld%lld", &a, &b);
        if (a > b)
            swap(a, b);
        ll ans = 0;
        if (a == b || a + 1 == b)
            ans += 2LL * a - 2;
        else
        {
            ll C = sqrt(1LL * a * b) - 1;
            while ((C + 1) * (C + 1) < 1LL * a * b)
                C++;
            if (C * (C + 1) >= 1LL * a * b)
                ans = 2LL * C - 2;
            else
                ans = 2LL * C - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}