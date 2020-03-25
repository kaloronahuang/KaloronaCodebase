// ARC100A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N];
long long suf[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ai[i] -= i;
    sort(ai + 1, ai + 1 + n);
    for (int i = n; i >= 1; i--)
        suf[i] = suf[i + 1] + ai[i];
    long long ans = 1e18, acc = 0;
    for (int i = 1; i <= n; i++)
    {
        int b = ai[i];
        acc += ai[i];
        ans = min(ans, 1LL * b * i - acc + suf[i + 1] - 1LL * (n - i) * b);
    }
    printf("%lld\n", ans);
    return 0;
}