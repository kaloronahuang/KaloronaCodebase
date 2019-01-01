// P2501.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const ll MX_N = 35020, INF = 0x3f3f3f3f;
ll head[MX_N], arr[MX_N], n, len, dst[MX_N], dp[MX_N], M_curt, f[MX_N], sum1[MX_N], sum2[MX_N];
struct edge
{
    ll to, nxt;
} edges[MX_N << 1];
void addpath(ll src, ll dst)
{
    edges[M_curt].to = dst, edges[M_curt].nxt = head[src];
    head[src] = M_curt++;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), arr[i] -= i, dst[i] = INF;
    dst[0] = -INF, dp[1] = 1, len = 1, dst[1] = arr[1], arr[0] = -INF, arr[++n] = INF;
    for (ll i = 2; i <= n; i++)
    {
        ll addr = upper_bound(dst, dst + 1 + len, arr[i]) - dst;
        len = max(len, addr);
        dp[i] = addr;
        dst[addr] = min(dst[addr], arr[i]);
    }
    printf("%lld\n", n - dp[n]);
    for (ll i = n; i >= 0; i--)
        addpath(dp[i], i), f[i] = INF;
    f[0] = 0;
    for (ll i = 1; i <= n; i++)
        for (ll e = head[dp[i] - 1]; e != -1; e = edges[e].nxt)
        {
            ll v = edges[e].to;
            if (v > i)
                break;
            if (arr[v] > arr[i])
                continue;
            for (ll k = v; k <= i; k++)
                sum1[k] = abs(arr[k] - arr[v]), sum2[k] = abs(arr[k] - arr[i]);
            for (ll k = v + 1; k <= i; k++)
                sum1[k] += sum1[k - 1], sum2[k] += sum2[k - 1];
            for (ll k = v; k <= i - 1; k++)
                f[i] = min(f[i], f[v] + sum1[k] - sum1[v] + sum2[i] - sum2[k]);
        }
    printf("%lld", f[n]);
    return 0;
}