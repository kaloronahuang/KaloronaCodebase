// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 100010;
ll arr[MAX_N], n, k;
priority_queue<ll> pq;
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    for (int i = 2; i <= n; i++)
        pq.push(arr[i - 1] - arr[i]);
    ll ans = 0;
    for (int i = 1; i <= k; i++)
        ans += (-pq.top()), pq.pop();
    printf("%lld", ans);
    return 0;
}