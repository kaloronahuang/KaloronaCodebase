// B.cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define ll long long
using namespace std;
const int MAX_N = 2e5 + 2000, mod = 1e9 + 7;
ll tree[MAX_N << 2], f[MAX_N], n, prefix[MAX_N], tmpx, k;
// the number domain still exists;
void add(int x, ll d)
{
    x += MAX_N;
    while (x <= 2 * MAX_N)
        tree[x] += d, x += lowbit(x);
}
ll sum(int x)
{
    x += MAX_N;
    ll ans = 0;
    while (x)
        ans += tree[x], x -= lowbit(x);
    return ans;
}
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &tmpx), prefix[i] = prefix[i - 1] + ((tmpx == 1) ? 1 : -1);
    add(0, 1);
    for (int i = 1; i <= n; i++)
        f[i] = (sum(prefix[i] + k) - sum(prefix[i] - k - 1) + mod) % mod, add(prefix[i], f[i]);
    printf("%lld", f[n]);
    return 0;
}