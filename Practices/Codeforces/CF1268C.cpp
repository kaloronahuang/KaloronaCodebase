// CF1268C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

ll n, pi[MAX_N], pos[MAX_N], nodes[2][MAX_N], inv_f[MAX_N], ans[MAX_N];
bool vis[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int id, int x, ll d)
{
    for (; x <= n; x += lowbit(x))
        nodes[id][x] += d;
}

ll query(int id, int x, ll ret = 0)
{
    for (; x > 0; x -= lowbit(x))
        ret += nodes[id][x];
    return ret;
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &pi[i]), pos[pi[i]] = i;
    for (int i = 1; i <= n; i++)
    {
        inv_f[i] = inv_f[i - 1] + i - query(0, pos[i]) - 1;
        update(0, pos[i], 1);
    }
    memset(nodes[0], 0, sizeof(nodes[0]));
    ll LB = n, RB = 1;
    for (int i = 1; i <= n; i++)
        update(0, i, 1), update(1, i, i), vis[i] = true;
    for (int i = 1; i <= n; i++)
    {
        LB = min(LB, pos[i]), RB = max(RB, pos[i]);
        update(0, pos[i], -1), update(1, pos[i], -pos[i]), vis[pos[i]] = false;
        int l = LB, r = RB, res = LB;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            int l_key = query(0, mid - 1) - query(0, LB);
            int r_key = query(0, RB) - query(0, mid);
            l_key = mid - LB - l_key, r_key = RB - mid - r_key;
            if (l_key <= r_key)
                res = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        ll k1 = query(1, res) - query(1, LB), k1_ = query(0, res) - query(0, LB);
        ll k2 = query(1, RB) - query(1, res), k2_ = query(0, RB) - query(0, res);
        ans[i] = (k1 - k1_ * LB - (k1_ * (k1_ - 1) / 2)) + (k2_ * RB - k2 - (k2_ * (k2_ - 1) / 2));
    }
    for (int i = 1; i <= n; i++)
        printf("%lld ", inv_f[i] + ans[i]);
    return 0;
}