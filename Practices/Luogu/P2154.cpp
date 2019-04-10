// P2154.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 100100, mod = 2147483648;
ll n, m, k, w;
ll C[MAX_N][15], tree[MAX_N], btmpx[MAX_N << 1], bxtot;
ll xtot[MAX_N], ytot[MAX_N], last[MAX_N], lasty[MAX_N];
ll lenY, btmpy[MAX_N << 1], bytot;
struct pr
{
    ll first, second;
    bool operator<(const pr &p) const { return first < p.first || (p.first == first && second < p.second); }
} prs[MAX_N];
inline ll lowbit(int x) { return x & (-x); }
void add(int x, ll d)
{
    while (x <= lenY)
        tree[x] = (tree[x] + d + mod) % mod, x += lowbit(x);
}
ll sum(int x)
{
    if (x == 0)
        return 0;
    ll ans = 0;
    while (x)
        ans = (ans + tree[x] + mod) % mod, x -= lowbit(x);
    return ans;
}
void place(int y)
{
    if (last[y])
        add(y, -last[y]), last[y] = 0;
    lasty[y]++;
    if (lasty[y] >= k && ytot[y] - lasty[y] >= k)
        last[y] = C[lasty[y]][k] * C[ytot[y] - lasty[y]][k] % mod, add(y, last[y]);
}
ll query(ll l, ll r)
{
    if (l > r)
        return 0;
    return sum(r) - sum(l - 1);
}
int main()
{
    scanf("%lld%lld%lld", &n, &m, &w);
    for (int i = 1; i <= w; i++)
        scanf("%lld%lld", &prs[i].first, &prs[i].second), btmpx[++bxtot] = prs[i].first, btmpy[++bytot] = prs[i].second;
    scanf("%lld", &k);
    sort(btmpx + 1, btmpx + 1 + bxtot), sort(btmpy + 1, btmpy + 1 + bytot);
    bxtot = unique(btmpx + 1, btmpx + 1 + bxtot) - btmpx - 1;
    bytot = unique(btmpy + 1, btmpy + 1 + bytot) - btmpy - 1;

    for (int i = 1; i <= w; i++)
    {
        prs[i].first = lower_bound(btmpx + 1, btmpx + 1 + bxtot, prs[i].first) - btmpx;
        prs[i].second = lower_bound(btmpy + 1, btmpy + 1 + bytot, prs[i].second) - btmpy;
        xtot[prs[i].first]++, ytot[prs[i].second]++;
        lenY = max(lenY, prs[i].second);
    }
    sort(prs + 1, prs + 1 + w);
    C[0][0] = 1;
    for (int i = 1; i <= w; i++)
        for (int j = 0; j <= k; j++)
            C[i][j] = (C[i - 1][j] + (j ? C[i - 1][j - 1] : 0)) % mod;
    ll ans = 0, xcnt = 0, lx = -1;
    for (int i = 1; i <= w; i++)
    {
        if (lx != prs[i].first)
            xcnt = 0, lx = prs[i].first;
        xcnt++;
        if (xcnt >= k && xtot[lx] - xcnt >= k && prs[i + 1].first == lx)
            ans = (ans + ((C[xcnt][k] * C[xtot[lx] - xcnt][k] % mod) * query(prs[i].second + 1, prs[i + 1].second - 1) % mod)) % mod;
        place(prs[i].second);
    }
    printf("%lld", (ans + mod) % mod);
    return 0;
}