// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N << 1];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= (n << 1); i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + (n << 1));
    long long ans = 1e18;
    for (int i = 1; i <= n; i++)
        ans = min(ans, 1LL * (ai[i + n - 1] - ai[i]) * (ai[n << 1] - (i == 1 ? ai[n + 1] : ai[1])));
    printf("%lld\n", ans);
    return 0;
}