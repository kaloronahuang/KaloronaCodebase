// FOJ3158.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int num[(int)1e6], cnt;
int main()
{
    ll tot = 1, n;
    scanf("%lld", &n);
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i)
            continue;
        cnt++;
        while (n % i == 0)
            n /= i, num[cnt]++;
    }
    if (n != 1)
        num[++cnt] = 1;
    ll ans = 1;
    for (register int i = 1; i <= cnt; i++)
        ans *= ((num[i] << 1) | 1);
    printf("%lld", (ans + 1) >> 1);
    return 0;
}