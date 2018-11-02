// sleep.cpp
#include <iostream>
#include <cstdio>
using namespace std;
// bao int;
#define ll long long
const int maxn = 1000020;
ll a[maxn];
ll b[maxn];
ll suma[maxn];
ll times[maxn];
ll N, k;

ll query(ll l, ll r)
{
    if (l == r)
        return suma[l] - suma[l - 1];
    return suma[r] - suma[l - 1] + times[l - 1] + times[N] - times[r];
}

int main()
{
    freopen("sleep.in", "r", stdin);
    freopen("sleep.out", "w", stdout);
    suma[0] = 0;
    times[0] = 0;
    scanf("%lld%lld", &N, &k);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &a[i]), suma[i] = suma[i - 1] + a[i];
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld", &b[i]);
        times[i] = times[i - 1] + a[i] * b[i];
    }
    ll ans = 0;
    for (int i = 1; i + k - 1 <= N; i++)
        ans = max(query(i, i + k - 1), ans);
    printf("%lld", ans);
    return 0;
}