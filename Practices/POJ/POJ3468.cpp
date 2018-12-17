// POJ3468.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
#define lowbit(num) (num & -num)
using namespace std;
const int maxn = 100200;
ll arr[maxn], n, tree[2][maxn], sum[maxn], m;
void add(ll x, ll c, int id)
{
    while (x <= n)
        tree[id][x] += c, x += lowbit(x);
}
ll query(int x, int k)
{
    ll res = 0;
    while (x > 0)
        res += tree[k][x], x -= lowbit(x);
    return res;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), sum[i] = sum[i - 1] + arr[i];
    while (m--)
    {
        char opt[2];
        int a, b, c;
        scanf("%s%d%d", opt, &a, &b);
        if (opt[0] == 'Q')
        {
            ll ans = (sum[b] + (b + 1) * query(b, 0) - query(b, 1)) - (sum[a - 1] + a * query(a - 1, 0) - query(a - 1, 1));
            printf("%lld\n", ans);
        }
        else
        {
            scanf("%d", &c);
            add(a, c, 0);
            add(b + 1, -c, 0);
            add(a, a * c, 1);
            add(b + 1, -(b + 1) * c, 1);
        }
    }
    return 0;
}