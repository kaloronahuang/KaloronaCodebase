// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 3e5 + 2000;
ll n, m, arr[MAX_N], cp[MAX_N], sum[MAX_N];
bool cmp(ll a, ll b) { return a > b; }
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    sort(arr + 1, arr + 1 + n, cmp);
    for (ll i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + arr[i];
    scanf("%lld", &m);
    for (ll i = 1; i <= m; i++)
        scanf("%lld", &cp[i]), printf("%lld\n", sum[cp[i] - 1] + sum[n] - sum[cp[i]]);
    return 0;
}