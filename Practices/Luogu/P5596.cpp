// P5596.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ll a, b, ans = 0;
    scanf("%lld%lld", &a, &b);
    for (ll i = 0; i <= max((ll)(sqrt(b)), a / 2); i++)
    {
        ll upper = b - 1LL * i * i, denominator = 2LL * i - a;
        if (upper == 0 && denominator == 0)
            printf("inf"), exit(0);

        if ((upper > 0 && denominator > 0) || (upper < 0 && denominator < 0) || upper == 0)
            if (upper % denominator == 0)
                ans++;
    }
    printf("%lld", ans);
    return 0;
}