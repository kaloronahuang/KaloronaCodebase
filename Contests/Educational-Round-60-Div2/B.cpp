// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, k, arr[(int)2e5 + 100];
int main()
{
    scanf("%I64d%I64d%I64d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%I64d", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    ll mx = arr[n], mxs = arr[n - 1];
    ll segs = m / (k + 1), remain = m % (k + 1);
    ll ans = segs * (mxs + mx * k) + remain * mx;
    printf("%I64d", ans);
    return 0;
}