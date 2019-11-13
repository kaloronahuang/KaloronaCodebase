// P2125.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 5001001;

ll sum, ai[MAX_N], n, ci[MAX_N], x1, org[MAX_N];

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), sum += ai[i];
    sum /= n;
    for (int i = 1; i <= n; i++)
        ci[i] = org[i] = ci[i - 1] + ai[i] - sum;
    nth_element(ci + 1, ci + (n >> 1) + 1, ci + 1 + n), x1 = ci[(n >> 1) + 1];
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += llabs(ci[i] - x1);
    printf("%lld\n", ans);
    for (int i = 1; i < n; i++)
        printf("%lld %lld\n", x1 - org[i - 1], -(x1 - org[i]));
    printf("%lld %lld\n", x1 - org[n - 1], -x1);
    return 0;
}