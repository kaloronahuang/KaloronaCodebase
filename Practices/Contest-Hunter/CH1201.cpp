// CH1201.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
const int maxn = 300200;
ll n, arr[maxn], sum[maxn], m, q[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), sum[i] = sum[i - 1] + arr[i];
    ll l = 1, r = 1, ans = -1e9;
    q[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (l <= r && q[l] < i - m)
            l++;
        ans = max(ans, sum[i] - sum[q[l]]);
        while (l <= r && sum[q[r]] >= sum[i])
            r--;
        q[++r] = i;
    }
    printf("%lld", ans);
    return 0;
}