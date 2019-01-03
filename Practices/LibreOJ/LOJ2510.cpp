// LOJ2510.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
const ll MX_N = 20010;
ll n, dp[MX_N][42][42], son[MX_N][2];
struct node
{
    ll a, b, c;
} nodes[MX_N << 1];
ll dfs(ll u, ll trk, ll rt)
{
    if (u < 0)
        return nodes[-u + n].c * (nodes[-u + n].a + trk) * (nodes[-u + n].b + rt);
    if (dp[u][trk][rt] == -1)
        dp[u][trk][rt] = min(dfs(son[u][1], trk, rt + 1) + dfs(son[u][0], trk, rt), dfs(son[u][1], trk, rt) + dfs(son[u][0], trk + 1, rt));
    return dp[u][trk][rt];
}
int main()
{
    scanf("%lld", &n);
    memset(dp, -1, sizeof(dp));
    for (ll i = 1; i <= n - 1; i++)
        scanf("%lld%lld", &son[i][0], &son[i][1]);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &nodes[i + n].a, &nodes[i + n].b, &nodes[i + n].c);
    printf("%lld", dfs(1, 0, 0));
    return 0;
}