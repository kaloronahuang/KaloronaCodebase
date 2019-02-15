// FOJ2930.cpp
#include <bits/stdc++.h>
#define ll long long
#define lowbit(p) (p & -p)
using namespace std;
const ll MAX_N = 1e5 + 200;
ll n, l, c, spd[MAX_N], mxspd, f[MAX_N], tree[1000100];
void update(int num)
{
    num++;
    while (num <= mxspd)
        tree[num] += 1, num += lowbit(num);
}
ll sum(int num)
{
    num++;
    ll ans = 0;
    while (num)
        ans += tree[num], num -= lowbit(num);
    return ans;
}
int main()
{
    scanf("%lld%lld%lld", &n, &l, &c);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &spd[i]);
    sort(spd + 1, spd + 1 + n), mxspd = spd[n];
    for (int i = 1; i <= n; i++)
        f[i] = (l * spd[i]) / mxspd;
    update((l * spd[1]) % mxspd);
    ll prefix = f[1], ans = 0;
    for (int i = 2; i <= n; i++)
    {
        prefix += f[i];
        ans += i * f[i] - prefix - i;
        update((l * spd[i]) % mxspd);
        ans += sum((l * spd[i]) % mxspd);
    }
    printf("%lld", ans);
    return 0;
}