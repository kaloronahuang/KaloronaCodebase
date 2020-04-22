// BZ2253.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50100;

int n, base, mod, dp[MAX_N], tree[MAX_N];
vector<int> mpz;

struct node
{
    int x, y, z, id;
} nodes[MAX_N];

int ripe(vector<int> &src, int x) { return lower_bound(src.begin(), src.end(), x) - src.begin() + 1; }

int fpow(int bas, int tim)
{
    int ret = 1;
    for (; tim; tim >>= 1, bas = 1LL * bas * bas % mod)
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
    return ret;
}

inline int lowbit(int x) { return x & (-x); }

void clear(int x)
{
    for (; x <= n; x += lowbit(x))
        tree[x] = 0;
}

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] = max(tree[x], d);
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, tree[x]);
    return ret;
}

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = -1, tl = (l + r) >> 1, tr = tl + 1;
    while (tl >= l || tr <= r)
    {
        if (tl >= l && nodes[tl].x != nodes[tl + 1].x)
        {
            mid = tl;
            break;
        }
        if (tr <= r && nodes[tr - 1].x != nodes[tr].x)
        {
            mid = tr - 1;
            break;
        }
        tl--, tr++;
    }
    if (mid == -1)
        return;
    solve(l, mid);
    sort(nodes + l, nodes + mid + 1, [](const node &rhs1, const node &rhs2) { return rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.z < rhs2.z); });
    sort(nodes + mid + 1, nodes + r + 1, [](const node &rhs1, const node &rhs2) { return rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.z < rhs2.z); });
    for (int i = mid + 1, lptr = l; i <= r; i++)
    {
        while (lptr <= mid && nodes[lptr].y < nodes[i].y)
            update(nodes[lptr].z, dp[nodes[lptr].id]), lptr++;
        dp[nodes[i].id] = max(dp[nodes[i].id], query(nodes[i].z - 1) + 1);
    }
    for (int i = mid + 1, lptr = l; i <= r; i++)
        while (lptr <= mid && nodes[lptr].y < nodes[i].y)
            clear(nodes[lptr].z), lptr++;
    sort(nodes + mid + 1, nodes + 1 + r, [](const node &rhs1, const node &rhs2) { return rhs1.x < rhs2.x || (rhs1.x == rhs2.x && (rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.z < rhs2.z))); });
    solve(mid + 1, r);
}

int main()
{
    scanf("%d%d%d", &base, &mod, &n);
    for (int i = 1; i <= n; i++)
    {
        int arr[3] = {fpow(base, 3 * i - 2), fpow(base, 3 * i - 1), fpow(base, 3 * i)};
        sort(arr, arr + 3);
        nodes[i].x = arr[0];
        nodes[i].y = arr[1];
        mpz.push_back(nodes[i].z = arr[2]);
    }
    sort(mpz.begin(), mpz.end()), mpz.erase(unique(mpz.begin(), mpz.end()), mpz.end());
    for (int i = 1; i <= n; i++)
    {
        nodes[i].z = ripe(mpz, nodes[i].z);
        nodes[i].id = i, dp[i] = 1;
    }
    sort(nodes + 1, nodes + 1 + n, [](const node &rhs1, const node &rhs2) { return rhs1.x < rhs2.x || (rhs1.x == rhs2.x && (rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.z < rhs2.z))); });
    solve(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    printf("%d\n", ans);
    return 0;
}