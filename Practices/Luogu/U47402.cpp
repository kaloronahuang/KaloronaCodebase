// U47402.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define lowbit(x) (x & -x)
#define ll long long
using namespace std;
const ll MAX_N = 102000;
struct node
{
    ll x, y;
    bool operator<(const node &nd) const { return x < nd.x || ((nd.x == x) && y < nd.y); }
} nodes[MAX_N];
ll n, tree[MAX_N], ans;
ll sum(ll x)
{
    ll ret = 0;
    while (x > 0)
        ret += tree[x], x -= lowbit(x);
    return ret;
}
void add(ll x, ll d)
{
    while (x < MAX_N)
        tree[x] += d, x += lowbit(x);
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld", &nodes[i].x, &nodes[i].y);
    sort(nodes + 1, nodes + 1 + n);
    for (ll i = 1; i <= n; i++)
    {
        ll now = sum(nodes[i].y);
        ans += now;
        add(nodes[i].y, 1);
    }
    printf("%lld", ans);
    return 0;
}