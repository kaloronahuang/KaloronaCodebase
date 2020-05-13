// CF1349A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n;
ll ai[MAX_N], pre[MAX_N], suf[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    pre[1] = ai[1], suf[n] = ai[n];
    for (int i = 2; i <= n; i++)
        pre[i] = __gcd(pre[i - 1], ai[i]);
    for (int i = n - 1; i >= 1; i--)
        suf[i] = __gcd(suf[i + 1], ai[i]);
    for (int i = 1; i <= n; i++)
    {
        ll d = __gcd(pre[i - 1], suf[i + 1]);
        ai[i] = ai[i] * d / __gcd(ai[i], d);
    }
    ll d = ai[1];
    for (int i = 2; i <= n; i++)
        d = __gcd(d, ai[i]);
    printf("%lld\n", d);
    return 0;
}