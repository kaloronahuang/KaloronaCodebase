// challenge.cpp
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;
const unsigned MAGIC_NUM = 4294967295u;

ll ai[MAX_N], wi[MAX_N], n, q, block_siz, block_tot, lft[MAX_N];
pair<ll, int> tmp[MAX_N];
ll pre[MAX_N], tree[MAX_N];

int lowbit(int x) { return x & (-x); }

void update(int x, ll d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += d;
}

ll query(int x)
{
    ll ans = 0;
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

unsigned xnor(unsigned a, unsigned b) { return ~((a & MAGIC_NUM) ^ (b & MAGIC_NUM)); }

void rebuild(int id)
{
    for (int i = lft[id]; i <= lft[id + 1] - 1; i++)
        tmp[i] = make_pair(wi[i], i);
    sort(tmp + lft[id], tmp + lft[id + 1]);
    pre[lft[id]] = wi[tmp[lft[id]].second] * ai[tmp[lft[id]].second];
    for (int i = lft[id] + 1; i <= lft[id + 1] - 1; i++)
        pre[i] = pre[i - 1] + wi[tmp[i].second] * ai[tmp[i].second];
}

int main()
{
    scanf("%lld%lld", &n, &q);
    block_siz = sqrt(n), block_tot = (n + block_siz - 1) / block_siz;
    lft[1] = 1, lft[block_tot + 1] = n + 1;
    for (int i = 2; i <= block_tot; i++)
        lft[i] = lft[i - 1] + block_siz;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), update(i, ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]);
    for (int i = 1; i <= block_tot; i++)
        rebuild(i);
    while (q--)
    {
        ll op, x, y, z;
        scanf("%lld%lld%lld", &op, &x, &y);
        if (op == 1)
        {
            scanf("%lld", &z);
            unsigned ans = 0, pans = query(y) - query(x - 1);
            int xid = (x + block_siz - 1) / block_siz, yid = (y + block_siz - 1) / block_siz;
            if (xid != yid)
            {
                for (int i = xid + 1; i <= yid - 1; i++)
                {
                    int pos = lower_bound(tmp + lft[i], tmp + lft[i + 1], make_pair(z + 1, 0)) - tmp - 1;
                    ans += pos >= lft[i] ? pre[pos] : 0;
                }
                for (int i = x; i <= lft[xid + 1] - 1; i++)
                    if (wi[i] <= z)
                        ans += wi[i] * ai[i];
                for (int i = lft[yid]; i <= y; i++)
                    if (wi[i] <= z)
                        ans += wi[i] * ai[i];
            }
            else
                for (int i = x; i <= y; i++)
                    if (wi[i] <= z)
                        ans += wi[i] * ai[i];
            printf("%u\n", xnor(ans, pans));
        }
        else if (op == 2)
        {
            update(x, -ai[x]), ai[x] = y;
            rebuild((x + block_siz - 1) / block_siz);
            update(x, ai[x]);
        }
        else
        {
            wi[x] = y;
            rebuild((x + block_siz - 1) / block_siz);
        }
    }
    return 0;
}